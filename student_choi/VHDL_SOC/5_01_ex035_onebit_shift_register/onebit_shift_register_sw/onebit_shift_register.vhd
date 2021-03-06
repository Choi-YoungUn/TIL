library ieee;
use ieee.std_logic_1164.all;

entity onebit_shift_register is
port ( rset : in std_logic;
       clk : in  std_logic;
		 data : in std_logic;
		 q : out std_logic_vector(3 downto 0));
		 end onebit_shift_register;
		 
		 architecture behav of onebit_shift_register is
		 signal temp : std_logic_vector(3 downto 0);
		 
		 begin
		 process(rset, clk)
		 begin
		 if(rset = '1') then
		 temp <= "0000";
		 elsif(clk'event and clk = '1') then
		 temp <= temp(2 downto 0) & data;
		 end if;
		 end process;
		 
		 q <= temp;
		 
		 end behav;