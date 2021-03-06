library ieee;
use ieee.std_logic_1164.all;

entity fivebitand is
port (a : in std_logic_vector(4 downto 0);
      s : in std_logic_vector(1 downto 0);
		
		yo : out std_logic_vector(4 downto 0)
		);
		end fivebitand;
		
		architecture dataflow of fivebitand is
		begin
		yo(0) <= a(0) and (not(s(1) or s(0)));
		yo(1) <= a(1) and (not(s(1) or s(0)));
		yo(2) <= a(2) and (not(s(1) or s(0)));
		yo(3) <= a(3) and (not(s(1) or s(0)));
		yo(4) <= a(4) and (not(s(1) or s(0)));
		end dataflow;