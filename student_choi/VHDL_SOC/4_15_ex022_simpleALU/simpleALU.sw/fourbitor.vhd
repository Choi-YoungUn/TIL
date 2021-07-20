library ieee;
use ieee.std_logic_1164.all;

entity fourbitor is
port (a : in std_logic_vector(3 downto 0);
      b : in std_logic_vector(3 downto 0);
		s : in std_logic_vector(1 downto 0);
		
		yo : out std_logic_vector(3 downto 0)
		);
		end fourbitor;
		
		architecture dataflow of fourbitor is
		begin
		yo(0) <= (a(0) or b(0))and (not s(1)and s(0));
		yo(1) <= (a(1) or b(1))and (not s(1)and s(0));
		yo(2) <= (a(2) or b(2))and (not s(1)and s(0));
		yo(3) <= (a(3) or b(3))and (not s(1)and s(0));
		end dataflow;
		