library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity fourbitcomparator is
port (Ai : in std_logic_vector(0 to 3);  --IN PUT  A
      Bi : in std_logic_vector(0 to 3);  --IN PUT  B
		Xif : in std_logic;       --하위 비교 A > B
		Yif : in std_logic;       --하위 비교 A = B
		Zif : in std_logic;       --하위 비교 A < B
		
		Xof : out std_logic;   --A > B
		Yof : out std_logic;   --A = B
		Zof : out std_logic);  --A < B
		end fourbitcomparator;
		
		architecture sample of fourbitcomparator is
		
		component onebitfullcomparator_vh is  --component선언
	 port ( A : in std_logic;
       B : in std_logic;
		 Xi : in std_logic;
		 Yi : in std_logic;
		 Zi : in std_logic;
		 
		 Xo : out std_logic;
		 Yo : out std_logic;
		 Zo : out std_logic);
		 end component;
		
		signal x : std_logic_vector(3 downto 1);   --신호 자료형 선언
		signal y : std_logic_vector(3 downto 1);
		signal z : std_logic_vector(3 downto 1);
		
		begin
		u3 : onebitfullcomparator_vh  --맨 하위 비트 비교 
		port map( A => Ai(3),  B => Bi(3), Xi => Xif, Yi => Yif,  Zi => Zif,	--포트맵 대입
					Xo => x(3), Yo => y(3), Zo => z(3));
		 u2 : onebitfullcomparator_vh --두번째 비트 비교
		port map( A => Ai(2), B => Bi(2),Xi => x(3), Yi => y(3), Zi => z(3),	--포트맵 대입
					Xo => x(2), Yo => y(2), Zo => z(2));
		 u1 : onebitfullcomparator_vh --세번째 비트 비교
		port map( A => Ai(1), B => Bi(1), Xi => x(2), Yi => y(2), Zi => z(2),--포트맵 대입
					Xo => x(1), Yo => y(1), Zo => z(1));
		 u0 : onebitfullcomparator_vh --제일 상위 비트 비교
		port map( A => Ai(0), B => Bi(0), Xi => x(1), Yi => y(1), Zi => z(1),--포트맵 대입
					Xo => Xof, Yo => Yof, Zo => Zof);
		
		end sample;