library ieee;
use ieee.std_logic_1164.all;

entity fourbitand is
port (a : in std_logic_vector(3 downto 0);
      b : in std_logic_vector(3 downto 0);
		s : in std_logic_vector(1 downto 0);
		
		yo : out std_logic_vector(3 downto 0)
		);
		end fourbitand;
		
		architecture dataflow of fourbitand is
		begin
		yo(0) <= (a(0) and b(0))and (s(1)and (not s(0)));
		yo(1) <= (a(1) and b(1))and (s(1)and (not s(0)));
		yo(2) <= (a(2) and b(2))and (s(1)and (not s(0)));
		yo(3) <= (a(3) and b(3))and (s(1)and (not s(0)));
		end dataflow;
		