library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity myrommemory is
   port( addr : in std_logic_vector(2 downto 0);
	      
			data : out std_logic_vector(7 downto 0));
			end myrommemory;
			
			architecture example of myrommemory is
			
			subtype rom_word is std_logic_vector(7 downto 0);
			type rom_table is array (0 to 7) of rom_word;
			
			constant myrommemory : rom_table :=
			("00000001", 
			 "00000010",
			 "00000100",
			 "00001000",
			 "00010000",
			 "00100000",
			 "01000000",
			 "10000000");
			 
			 begin
			 process (addr)
			 variable read_addr : integer range 0 to 7;
			 begin
			 read_addr := conv_integer(addr);
			 data <= myrommemory(read_addr);
			 end process;
			 
			 end example;