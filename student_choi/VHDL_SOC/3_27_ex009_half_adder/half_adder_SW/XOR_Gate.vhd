library ieee;
use ieee.std_logic_1164.all;

entity XOR_Gate is
    port(A,B: in std_logic;
	 C : out std_logic);
	 end XOR_Gate;
	 
	 architecture Dataflow of XOR_Gate is
	 begin
	   C <=(A xor B);
		end Dataflow;