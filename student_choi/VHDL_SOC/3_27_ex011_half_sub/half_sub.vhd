library ieee;
use ieee.std_logic_1164.all;

entity half_sub is

port(x, y : in std_logic;
     D, BO : out std_logic);
	  end half_sub;
	  
	  architecture Dataflow of half_sub is
	  begin
	   D <= x xor y;
		BO <= (not x) and y;
		end Dataflow;
		