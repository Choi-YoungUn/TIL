library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity myrammemory is
generic (addr_bits : integer := 3;
         data_bits : integer := 8);
			
			port(
			w_en : in std_logic;
			addr : in std_logic_vector(addr_bits-1 downto 0);
			data_in : in std_logic_vector(data_bits-1 downto 0);
			data_out : out std_logic_vector(data_bits-1 downto 0);
			memclk : in std_logic);
			
			end myrammemory;
			
			architecture example of myrammemory is
			
			subtype ram_word is std_logic_vector(data_bits-1 downto 0);
			type ram_memory is array (0 to 2**addr_bits-1)of ram_word; 
			
			signal myrammemory : ram_memory :=
			("00000001",
			 "00000010",
			 "00000100",
			 "00001000",
			 "00010000",
			 "00100000",
			 "01000000",
			 "10000000");
			 
			 begin
			 process(memclk)
			 variable write_addr : integer range 0 to 2**addr_bits-1;
			 begin
			 if memclk = '1' and memclk'event then
			 if w_en = '1' then
			 write_addr := conv_integer(addr);
			 myrammemory(write_addr) <= data_in;
			 end if;
			 end if;
			 end process;
			 
			 process(addr)
			 variable read_addr : integer range 0 to 2**addr_bits-1;
			 begin
			 read_addr := conv_integer(addr);
			 data_out <= myrammemory(read_addr);
			 end process;
			 end example;
