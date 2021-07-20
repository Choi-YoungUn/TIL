library ieee;
use ieee.std_logic_1164.all;

entity XOR_VHDL is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end XOR_VHDL;
	 
	 architecture Behavioral of XOR_VHDL is
	 begin
	   process(A,B)
		begin
		if (A='1' and B= '1') or (A='0' and B= '0') then C<= '0' ;
		else C<='1' ;
		end if;
		end process;
		end Behavioral;