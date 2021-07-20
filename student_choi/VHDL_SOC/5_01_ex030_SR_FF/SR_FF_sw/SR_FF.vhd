library ieee;
use ieee.std_logic_1164.all;

entity SR_FF is
port (s : in std_logic;
      r : in std_logic;
	   clk : in std_logic;
	   preset : in std_logic;
	   clear : in std_logic;
		
	   Q : out std_logic;
	   Q_ber : out std_logic);
		end SR_FF;
		
		architecture behav of SR_FF is
		
		signal temp : std_logic;
		
		begin 
		
		process(preset, clear, clk)
		begin
		
		if(preset = '1') then
		temp <= '1';
		elsif(clear = '1') then
		temp <= '0';
		elsif(clk'event and clk = '1') then
		if    (s = '0' and r = '0') then
		temp <= temp;
		elsif (s = '1' and r = '0') then
		temp <= '1';
		elsif (s = '0' and r = '1') then
		temp <= '0';
		else
		temp <= null;
		end if;
		end if;
		end process;
		
		Q <= temp;
		Q_ber <= not temp;
		
		end behav;