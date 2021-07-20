library ieee;
use ieee.std_logic_1164.all;

entity XOR_Gate is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end XOR_Gate;
	 
	 architecture Behavioral of XOR_Gate is
	 begin
	   process(A,B)
		begin
		if (A='1' and B= '1') or (A='0' and B= '0') then C<= '0' ;
		else C<='1' ;
		end if;
		end process;
		end Behavioral;