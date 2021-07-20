library ieee;
use ieee.std_logic_1164.all;

entity fourbitand is
port (a : in std_logic_vector(3 downto 0);
      b : in std_logic_vector(3 downto 0);
		
		y : out std_logic_vector(3 downto 0)
		);
		end fourbitand;
		
		architecture dataflow of fourbitand is
		begin
		y(0) <= a(0) and b(0);
		y(1) <= a(1) and b(1);
		y(2) <= a(2) and b(2);
		y(3) <= a(3) and b(3);
		end dataflow;
		