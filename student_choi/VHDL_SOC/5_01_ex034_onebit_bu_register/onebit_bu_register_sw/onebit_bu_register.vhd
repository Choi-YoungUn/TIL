library ieee;
use ieee.std_logic_1164.all;

entity onebit_bu_register is
port (rst : in std_logic;
      en : in std_logic;
		clk : in std_logic;
		d : in std_logic_vector(3 downto 0);
		q : out std_logic_vector(3 downto 0));
		end onebit_bu_register;
		
		architecture behav of onebit_bu_register is
		
		begin 
		process(rst, en, clk)
		begin
		if(rst = '1') then
		q <= "0000";
		elsif(en = '1') then
		if(clk'event and clk = '1') then
		q <= d;
		end if;
		end if;
		end process;
		
		end behav;