library ieee;
use ieee.std_logic_1164.all;

entity EX_VHDL is
    port(A,B,C: in std_logic;
	 F : out std_logic);
	 end EX_VHDL;
	 
	 architecture Behavioral of EX_VHDL is
	 begin
	   process(A,B,C)
		begin
		if  A='1' and (B= '0' or C= '0') then F<= '0' ;
		else F<='1' ;
		end if;
		end process;
		end Behavioral;