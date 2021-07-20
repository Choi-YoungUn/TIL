library ieee;
use ieee.std_logic_1164.all;

entity NAND_VHDL is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end NAND_VHDL;
	 
	 architecture Behavioral of NAND_VHDL is
	 begin
	   process(A,B)
		begin
		if (A='1' and B= '1') then C<= '0' ;
		else C<='1' ;
		end if;
		end process;
		end Behavioral;