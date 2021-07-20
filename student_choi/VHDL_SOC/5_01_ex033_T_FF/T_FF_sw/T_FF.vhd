library ieee;
use ieee.std_logic_1164.all;

entity T_FF is
port ( t : in std_logic;
      clk : in std_logic;
      pr : in std_logic;
		clr : in std_logic;
		q : out std_logic;
		q_ber : out std_logic);
		end T_FF;
		
		architecture behav of T_FF is
		signal temp : std_logic;
		begin
		
		process(pr, clr, clk)
		begin
		if(pr = '1') then 
		temp <= '1';
		elsif(clr = '1') then
		temp <= '0';
		elsif(clk'event and clk = '1') then
		if(t = '0') then
		temp <= temp;
		elsif(t = '1') then
		temp <= not temp;
		
	end if;
	end if;
	end process;
	q <= temp;
	q_ber <= not temp;
	
	end behav;