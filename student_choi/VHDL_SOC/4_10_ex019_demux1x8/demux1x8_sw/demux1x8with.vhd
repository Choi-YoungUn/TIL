library ieee;
use ieee.std_logic_1164.all;

entity demux1x8with is
port ( I : in std_logic;
       S : in std_logic_vector(2 downto 0);
		 Y : out std_logic_vector(7 downto 0));
		 end demux1x8with;
		 
		 architecture Dataflow_with_select_when of demux1x8with is
		 
		 begin
		 with S select
		 Y <= I & "0000000" when "111",
		     '0' & I & "000000" when "110",
			  "00" & I & "00000" when "101",
			  "000" & I & "0000" when "100",
		     "0000" & I & "000" when "011",
		     "00000" & I & "00" when "010",
		     "000000" & I & '0' when "001", 
			  "0000000" & I when others;
			  
			 end Dataflow_with_select_when;