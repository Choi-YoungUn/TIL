library ieee;
use ieee.std_logic_1164.all;

entity fourbitxor is
port (a : in std_logic_vector(3 downto 0);
      b : in std_logic_vector(3 downto 0);
		
		yo : out std_logic_vector(3 downto 0)
		);
		end fourbitxor;
		
		architecture dataflow of fourbitxor is
		begin
		yo(0) <= a(0) xor b(0);
		yo(1) <= a(1) xor b(1);
		yo(2) <= a(2) xor b(2);
		yo(3) <= a(3) xor b(3);
		end dataflow;
		