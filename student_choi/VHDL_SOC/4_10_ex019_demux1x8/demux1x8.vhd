library ieee;
use ieee.std_logic_1164.all;

entity demux1x8 is
port ( I : in std_logic;
       S : in std_logic_vector(2 downto 0);
		 Y : out std_logic_vector(7 downto 0));
		 end demux1x8;
		 
		 architecture Dataflow_when_else of demux1x8 is
		 
		 begin
		 Y <= I & "0000000" when S = "111" else 
		     '0' & I & "000000" when S = "110" else
			  "00" & I & "00000" when S = "101" else
			 "000" & I & "0000" when S = "100" else
			 "0000" & I & "000" when S = "011" else
			 "00000" & I & "00" when S = "010" else 
			 "000000" & I & '0' when S = "001" else 
			 "0000000" & I;
			 end Dataflow_when_else;