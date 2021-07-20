library ieee;
use ieee.std_logic_1164.all;

entity demux1x8_whenelse is
port ( I : in std_logic;
       S : in std_logic_vector(2 downto 0);
		 Y : out std_logic_vector(7 downto 0));
		 end demux1x8_whenelse;
		 
		 architecture Dataflow_when_else of demux1x8_whenelse is
		 
		 begin
		 Y <= I & "000" when S = "111" else 
		     '0' & I & "00" when S = "110" else
			  "00" & I & '0' when S = "101" else
			 "00" & I & '0' when S = "100" else
			 "00" & I & '0' when S = "011" else
			 "00" & I & '0' when S = "010" else 
			 "00" & I & '0' when S = "001" else 
			 "000" & I;
			 end Dataflow_when_else;