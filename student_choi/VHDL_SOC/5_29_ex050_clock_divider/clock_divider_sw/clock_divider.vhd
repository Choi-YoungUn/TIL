library ieee;
use ieee.std_logic_1164.all;

entity clock_divider is
port( reset : in std_logic;
      clk : in std_logic;
		clk_div10 : out std_logic);
		end clock_divider;
		
		architecture behav of clock_divider is
		
		signal cnt : integer range 0 to 4;
		signal sig : std_logic;
		
		begin
		process(reset, clk)
		begin
		if(reset = '1') then
		cnt <= 0;
		sig <= '0';
		elsif(clk'event and clk = '0') then
		if(cnt >= 4) then
		cnt <= 0;
		sig <= not(sig);
		else
		cnt <= cnt + 1;
		end if;
		end if;
		end process;
		clk_div10 <= sig;
		
		end behav;