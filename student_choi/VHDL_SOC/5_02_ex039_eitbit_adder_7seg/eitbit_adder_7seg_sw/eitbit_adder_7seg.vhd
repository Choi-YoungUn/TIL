library ieee;
use ieee.std_logic_1164.all;

entity eitbit_adder_7seg is
port( x : in std_logic_vector(7 downto 0); --입력 A
      y : in std_logic_vector(7 downto 0); --입력 B
		
		segziro : out std_logic_vector(6 downto 0);  --1의 자리 7SEGMENT
		segten : out std_logic_vector(6 downto 0);  --10의 자리 7SEGMENT
		seghund : out std_logic_vector(6 downto 0));  --100의 자리 7SEGMENT
		
		end eitbit_adder_7seg;
		
		architecture behav of eitbit_adder_7seg is
		
		component eibbit_adder_vhd is  --8비트 가산기
port (
       add_a : in std_logic_vector( 7 downto 0);
		 add_b : in std_logic_vector( 7 downto 0);
		 
		 add_sum : out std_logic_vector( 8 downto 0)
		 );
		 end component;
		 
		 component nine_bcd is --9비트 -> 12비트 BCD코드 변환기
port ( nbit : in std_logic_vector(8 downto 0);        
       bcdcord : out std_logic_vector(11 downto 0));
		 end component;
		 
		 component FNDdecoder is -- 7SEGMENT 디스플레이
port (data_in : in std_logic_vector(3 downto 0);
      seg : out std_logic_vector(6 downto 0));
		end component;
		
		signal summ : std_logic_vector(8 downto 0);  --신호 선언
		signal bcds : std_logic_vector(11 downto 0); --신호 선언
		
		begin
		
		eitbit_adder : eibbit_adder_vhd    --8비트 가산
		port map(add_a => x , add_b => y, add_sum => summ);
		
		bi_to_bcd : nine_bcd  --9비트 ->  12비트 BCD코드 변환기
		port map(nbit => summ, bcdcord => bcds);
		
		seg1 : FNDdecoder --1의자리 7SEGMENT 
		port map(data_in => bcds(3 downto 0), seg => segziro);
		
		seg2 : FNDdecoder--10의자리 7SEGMENT 
		port map(data_in => bcds(7 downto 4), seg => segten);
		
		seg3 : FNDdecoder--100의자리 7SEGMENT 
		port map(data_in => bcds(11 downto 8), seg => seghund);
		
		end behav;
		