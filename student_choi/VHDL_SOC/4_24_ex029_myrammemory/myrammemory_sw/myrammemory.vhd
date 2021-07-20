library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity myrammemory is
generic (addr_bits : integer := 3;  -- 주소 크기 정의
         data_bits : integer := 8);  --데이터 크기 정의	
port(
			w_en : in std_logic;  --쓰기 신호 입력
			addr : in std_logic_vector(addr_bits-1 downto 0); --주소 (3비트)
			data_in : in std_logic_vector(data_bits-1 downto 0); --입력시 데이터(8비트)
			data_out : out std_logic_vector(data_bits-1 downto 0);--출력시 데이터(8비트)
			memclk : in std_logic); --메모리 클럭 
			end myrammemory;
			
			architecture example of myrammemory is
			
			subtype ram_word is std_logic_vector(data_bits-1 downto 0);
			type ram_memory is array (0 to 2**addr_bits-1)of ram_word; --데이터 크기 
			                                   --주소크기에 따라 2의 N승 만큼 데이터 크기가 커진다.
			signal myrammemory : ram_memory :=  --주소 설정
			("00000001", "00000010", "00000100", "00001000",
			 "00010000", "00100000", "01000000", "10000000");
			 
			 begin
			 process(memclk)
			 variable write_addr : integer range 0 to 2**addr_bits-1;
			 begin
			 if memclk = '1' and memclk'event then  --클럭 설정
			 if w_en = '1' then  --쓰기 신호 입력시
			 write_addr := conv_integer(addr);  --데이터를 써야 할 주소 입력
			 myrammemory(write_addr) <= data_in;  --데이터 입력
			 end if;
			 end if;
			 end process;
			 
			 process(addr)
			 variable read_addr : integer range 0 to 2**addr_bits-1;
			 begin
			 read_addr := conv_integer(addr);--읽어낼 주소 선택
			 data_out <= myrammemory(read_addr); --데이터 출력(읽기)
			 end process;
			 end example;
