
library ieee;
use ieee.std_logic_1164.all;

entity OR_VHDL is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end OR_VHDL;
	 
	 architecture Behavioral of OR_VHDL is
	 begin
	   process(A,B)
		begin
		if (A='1' or B= '1') then C<= '1' ;
		else C<='0' ;
		end if;
		end process;
		end Behavioral;