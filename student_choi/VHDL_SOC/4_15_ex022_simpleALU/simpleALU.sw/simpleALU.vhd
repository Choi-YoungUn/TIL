library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity simpleALU is
port( Ai : in std_logic_vector(3 downto 0);  --입력포트
      Bi : in std_logic_vector(3 downto 0);  --입력포트
		Si : in std_logic_vector(1 downto 0);  --신호 입력포트
		
		Y : out std_logic_vector(4 downto 0)  --출력 포트
		);
		end simpleALU;
		
		architecture simple of simpleALU is
		component half_adder is  --반가산기
		port ( a : in std_logic;
             b : in std_logic;
             s : out std_logic;
             co : out std_logic
				 );
				 
end component;

      component full_adder is  --전가산기
      port (a : in std_logic;
            b : in std_logic;
	       	ci : in std_logic;
	       	s : out std_logic;
	      	co : out std_logic);
				
		end component;
		
      component fourbitxor is  --4비트 xor 게이트
		port (a : in std_logic_vector(3 downto 0);
            b : in std_logic_vector(3 downto 0);
	      	s : in std_logic_vector(1 downto 0);
	       	yo : out std_logic_vector(3 downto 0)
		);
		end component;
		
		component fourbitor is --4비트 or 게이트
		port (a : in std_logic_vector(3 downto 0);
            b : in std_logic_vector(3 downto 0);
	       	s : in std_logic_vector(1 downto 0);
	 	
	       	yo : out std_logic_vector(3 downto 0)
		);
		end component;
		
		component fourbitand is --4비트 and 게이트
		port (a : in std_logic_vector(3 downto 0);
            b : in std_logic_vector(3 downto 0);
	      	s : in std_logic_vector(1 downto 0);
	      	yo : out std_logic_vector(3 downto 0)
		);
		end component;
		
		component fouror is    --4비트 단순 or 게이트 
		port (a : in std_logic_vector(3 downto 0);
		      yo : out std_logic
		      );
		end component;
		
		component fivebitand is  --5비트 and 게이트
		port (a : in std_logic_vector(4 downto 0);
            s : in std_logic_vector(1 downto 0);
	      	yo : out std_logic_vector(4 downto 0)
		);
		end component;
		
		signal carry : std_logic_vector(2 downto 0);  --신호 선언
		signal sub0 : std_logic_vector(4 downto 0);
		signal sub1 : std_logic_vector(3 downto 0);
		signal txor : std_logic_vector(3 downto 0);
		signal tor : std_logic_vector(3 downto 0);
		signal tand : std_logic_vector(3 downto 0);
		
		
		begin
		
		plus0 : half_adder  --덧셈 기능 회로 포트맵
		port map (a => Ai(0), b => Bi(0), s => sub0(0), co => carry(0));
			 
	   plus1 : full_adder
		port map (a => Ai(1), b => Bi(1), ci => carry(0), s => sub0(1), co => carry(1));
			 
	   plus2 : full_adder
		port map (a => Ai(2), b => Bi(2), ci => carry(1), s => sub0(2), co => carry(2));
			 
		plus3 : full_adder
		port map (a => Ai(3), b => Bi(3), ci => carry(2), s => sub0(3), co => sub0(4));
			 
			 suband : fivebitand  --가산이후 선택신호를 통한 mux기능 1차 회로
			 port map (
		    a(0) => sub0(0),
			 a(1) => sub0(1),
			 a(2) => sub0(2),
			 a(3) => sub0(3),
			 a(4) => sub0(4),
			 s(0) => si(0),
			 s(1) => si(1),
			 
			 yo(0) => sub1(0),
			 yo(1) => sub1(1),
			 yo(2) => sub1(2),
			 yo(3) => sub1(3),
			 yo(4) => Y(4)
			 );
		
		orgate : fourbitor --4비트 or 게이트
		port map (
		a(0) => Ai(0),
		a(1) => Ai(1),
		a(2) => Ai(2),
		a(3) => Ai(3),
		b(0) => Bi(0),
		b(1) => Bi(1),
		b(2) => Bi(2),
		b(3) => Bi(3),
		s(0) => si(0),
		s(1) => si(1),
		
		yo(0)=> tor(0),
		yo(1)=> tor(1),
		yo(2)=> tor(2),
		yo(3)=> tor(3)
		);
		
		andgate : fourbitand --4비트 and 게이트
		port map (
		a(0) => Ai(0),
		a(1) => Ai(1),
		a(2) => Ai(2),
		a(3) => Ai(3),
		b(0) => Bi(0),
		b(1) => Bi(1),
		b(2) => Bi(2),
		b(3) => Bi(3),
		s(0) => si(0),
		s(1) => si(1),
		
		yo(0)=> tand(0),
		yo(1)=> tand(1),
		yo(2)=> tand(2),
		yo(3)=> tand(3)
		);
		
		xorgate : fourbitxor  --4비트 xor 게이트
		port map (
		a(0) => Ai(0),
		a(1) => Ai(1),
		a(2) => Ai(2),
		a(3) => Ai(3),
		b(0) => Bi(0),
		b(1) => Bi(1),
		b(2) => Bi(2),
		b(3) => Bi(3),
		s(0) => si(0),
		s(1) => si(1),
		
		yo(0)=> txor(0),
		yo(1)=> txor(1),
		yo(2)=> txor(2),
		yo(3)=> txor(3)
		);
		
		orfourbit0 : fouror  --선택신호를 통한 mux기능 2차 회로 
		port map(
		a(0) => sub1(0),
		a(1) => tor(0),
		a(2) => tand(0),
		a(3) => txor(0),
		
		yo => Y(0)
		);
		
		orfourbit1 : fouror  --선택신호를 통한 mux기능 2차 회로
		port map(
		a(0) => sub1(1),
		a(1) => tor(1),
		a(2) => tand(1),
		a(3) => txor(1),
		
		yo => Y(1)
		);
		
		orfourbit2 : fouror  --선택신호를 통한 mux기능 2차 회로
		port map(
		a(0) => sub1(2),
		a(1) => tor(2),
		a(2) => tand(2),
		a(3) => txor(2),
		
		yo => Y(2)
		);
		
		orfourbit3 : fouror  --선택신호를 통한 mux기능 2차 회로
		port map(
		a(0) => sub1(3),
		a(1) => tor(3),
		a(2) => tand(3),
		a(3) => txor(3),
		
		yo => Y(3)
		);
		
		end simple;