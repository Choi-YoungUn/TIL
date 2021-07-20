library ieee;
use ieee.std_logic_1164.all;

entity ring_count is
port ( reset : in std_logic;  --reset input
       clk : in std_logic;  --clk input
		 q : out std_logic_vector(3 downto 0)); --out put
		 end ring_count;
		 
		 architecture behav of ring_count is
		 
		 signal temp : std_logic_vector(3 downto 0); --inside sign
		 begin
		 process(reset, clk)
		 begin
		 if(reset = '1') then --reset 시 "0000"
		 temp <= "0000";
		 elsif(clk'event and clk = '1')then--상승 엣지시
		 if(temp = "0000" or temp(3) = '1')then --"0000" or "1000"시
		 temp <= "0001";              --"0001"로 변환
		 elsif(temp(0) = '1')then  --"0001"=>"0010"
		 temp <= "0010"; 
		 elsif(temp(1) = '1')then  --"0010" => "0100"
		 temp <= "0100";
		 elsif(temp(2) = '1')then  --"0100" => "1000"
		 temp <= "1000";
		 end if;
		 end if;
		 end process;
		 q <= temp;
		 end behav;