library ieee;
use ieee.std_logic_1164.all;

entity jonnson_count is
port ( reset : in std_logic;  --reset input
       clk : in std_logic;  --clk input
		 q : out std_logic_vector(3 downto 0)); --out put
		 end jonnson_count;
		 
		 architecture behav of jonnson_count is
		 
		 signal temp : std_logic_vector(3 downto 0); --inside sign
		 begin
		 process(reset, clk)
		 begin
		 if(reset = '1') then --reset 시 "0000"
		 temp <= "0000";
		 elsif(clk'event and clk = '1')then--상승 엣지시
		 if(temp = "0000")then
		 temp <= "0001";
		 elsif(temp = "0001")then--존슨 동작을 하게 함.
		 temp <= "0011";
		 elsif(temp = "0011")then
		 temp <= "0111";
		 elsif(temp = "0111")then
		 temp <= "1111";
		 elsif(temp = "1111")then
		 temp <= "1110";
		 elsif(temp = "1110")then
		 temp <= "1100";
		 elsif(temp = "1100")then
		 temp <= "1000";
		 elsif(temp = "1000")then
		 temp <= "0000";
		 end if;
		 end if;
		 end process;
		 q <= temp;
		 end behav;