library ieee;
use ieee.std_logic_1164.all;

entity NOT_VHDL is
    port(A: in std_logic;
	 C : out std_logic);
	 end NOT_VHDL;
	 
	 architecture Behavioral of NOT_VHDL is
	 begin
	   process(A)
		begin
		if (A='0') then C<= '1' ;
		else C<='0' ;
		end if;
		end process;
		end Behavioral;