library ieee;
use ieee.std_logic_1164.all;
use work.my_demux1x8.all;

entity demux1x8_pack_proce is   
    port (I : in std_logic;
	       S : in std_logic_vector(2 downto 0);
	       Y : out std_logic_vector(7 downto 0));
	 end demux1x8_pack_proce;
	 
	 architecture Behavioral of demux1x8_pack_proce is
	 
	 begin
	     process(I,S)
		  begin
		  demux1x8_proce(I,S,Y);
		  end process;
		  
		  end Behavioral;
	 
	 