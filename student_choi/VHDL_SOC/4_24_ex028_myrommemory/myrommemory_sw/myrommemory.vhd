library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity myrommemory is
   port( addr : in std_logic_vector(2 downto 0);  --IN PUT
	      
			data : out std_logic_vector(7 downto 0));  --DATA OUT PUT
			end myrommemory;
			
			architecture example of myrommemory is
			
			subtype rom_word is std_logic_vector(7 downto 0);  --DATA SIZE정의
			type rom_table is array (0 to 7) of rom_word; --데이터 주소 정의
			
			constant myrommemory : rom_table :=
			("00000001", "00000010", "00000100", "00001000",
			 "00010000", "00100000", "01000000", "10000000");
			 
			 begin
			 process (addr)
			 variable read_addr : integer range 0 to 7; --정수형 변수 정의 0~7범위
			 begin
			 read_addr := conv_integer(addr); --원하는 데이터가 있는 주소
			 data <= myrommemory(read_addr); --데이터 출력
			 end process;
			 
			 end example;