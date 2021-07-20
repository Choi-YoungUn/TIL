library ieee;
use ieee.std_logic_1164.all;

entity fouror is
port (a : in std_logic_vector(3 downto 0);
      
		yo : out std_logic
		);
		end fouror;
		
		architecture dataflow of fouror is
		begin
		yo <= a(0) or a(1) or a(2) or a(3); 
		end dataflow;
		