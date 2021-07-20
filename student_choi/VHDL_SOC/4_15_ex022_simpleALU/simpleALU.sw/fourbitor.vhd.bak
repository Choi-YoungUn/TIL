library ieee;
use ieee.std_logic_1164.all;

entity fourbitor is
port (a : in std_logic_vector(3 downto 0);
      b : in std_logic_vector(3 downto 0);
		
		y : out std_logic_vector(3 downto 0)
		);
		end fourbitor;
		
		architecture dataflow of fourbitor is
		begin
		y(0) <= a(0) or b(0);
		y(1) <= a(1) or b(1);
		y(2) <= a(2) or b(2);
		y(3) <= a(3) or b(3);
		end dataflow;
		