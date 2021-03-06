library ieee;
use ieee.std_logic_1164.all;

entity FNDdecoder is
port (data_in : in std_logic_vector(3 downto 0);
      seg : out std_logic_vector(6 downto 0));
		end FNDdecoder;
		
		architecture dataflow_when_else of FNDdecoder is
		
		begin
		seg <= "1000000" when data_in = "0000" else
		       "1111001" when data_in = "0001" else
			    "0100100" when data_in = "0010" else
			    "0110000" when data_in = "0011" else
			    "0011001" when data_in = "0100" else
			    "0010010" when data_in = "0101" else
			    "0000010" when data_in = "0110" else
			    "1011000" when data_in = "0111" else
			    "0000000" when data_in = "1000" else
			    "0010000" when data_in = "1001" else
			    "1111111";
				 
				 end dataflow_when_else;
			 