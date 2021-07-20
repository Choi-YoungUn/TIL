library ieee;
use ieee.std_logic_1164.all;

entity NOR_VHDL is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end NOR_VHDL;
	 
	 architecture Behavioral of NOR_VHDL is
	 begin
	   process(A,B)
		begin
		if (A='0' and B= '0') then C<= '1' ;
		else C<='0' ;
		end if;
		end process;
		end Behavioral;
