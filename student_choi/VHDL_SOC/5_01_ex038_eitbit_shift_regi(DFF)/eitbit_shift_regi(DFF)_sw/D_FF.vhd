library ieee;
use ieee.std_logic_1164.all;

entity D_FF is
port (D : in std_logic;
	   clk : in std_logic;
	   preset : in std_logic;
	   clear : in std_logic;
	   Q : out std_logic);
		end D_FF;
		
		architecture behav of D_FF is
		
		signal temp : std_logic;
		
		begin 
		
		process(preset, clear, clk)
		begin
		
		if(preset = '1') then
		temp <= '1';
		elsif(clear = '1') then
		temp <= '0';
		elsif(clk'event and clk = '1') then
		temp <= D;
		end if;
		
		end process;
		
		Q <= temp;
		
		
		end behav;