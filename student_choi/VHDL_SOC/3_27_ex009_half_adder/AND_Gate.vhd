library ieee;
use ieee.std_logic_1164.all;

entity AND_Gate is
     port(A,B : in std_logic;
	        C : out std_logic); 
 end AND_Gate;
			  
architecture  Dataflow of AND_Gate is
begin 
      C <= (A and B);
end Dataflow;