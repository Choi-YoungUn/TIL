library ieee;
use ieee.std_logic_1164.all;

entity NOT_Gate is
    port(A: in std_logic;
	 C : out std_logic);
	 end NOT_Gate;
	 
	 architecture Behavioral of NOT_Gate is
	 begin
	   process(A)
		begin
		if (A='0') then C<= '1' ;
		else C<='0' ;
		end if;
		end process;
		end Behavioral;