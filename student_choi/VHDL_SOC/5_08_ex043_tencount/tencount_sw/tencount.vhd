library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity tencount is
port (reset : in std_logic;  --reset input
      clk : in std_logic;    --clk input
		q : out std_logic_vector(3 downto 0));  --out put
		end tencount;
		
		architecture behav of tencount is
		
		signal temp : std_logic_vector(3 downto 0); --inside signal
		begin
		process(reset, clk)
		begin
		if(reset = '1') then  --reset ='1' then 출력 = "0000"
		temp <= "0000";
		elsif (clk'event and clk ='1') then  --clk 상승엣지 시
		temp <= temp + 1; --1 상승 
		end if;
		if(temp = "1010")then -- 숫자가 10 일시 0으로 바꿔줌
		temp <= "0000";
		end if;
		end process;
		q <= temp;--출력
		end behav;