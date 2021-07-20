library ieee;
use ieee.std_logic_1164.all;

entity AND_Gate is
       port(A,B : in std_logic;
		        C :out std_logic);
end AND_Gate;

architecture Behavioral of  AND_Gate is
begin
   process(A,B)
	begin
	if (A='1' and B='1') then C<='1';
	else  C<='0';
	end if;
	end process;
	end Behavioral;