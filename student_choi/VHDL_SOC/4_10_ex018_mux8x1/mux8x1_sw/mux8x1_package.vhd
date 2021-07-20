library ieee;
use ieee.std_logic_1164.all;
use work.my_mux8x1.all;  --내가 설정한 패키지를 사용 하겠다.

entity mux8x1_package is
port(I : in std_logic_vector(7 downto 0);  --입력포트 8비트.
     S : in std_logic_vector(2 downto 0);  --선택포트 3비트. (2의 3승.)
	  Y : out std_logic);  --한개의 출력 포트.
	  end mux8x1_package;
	  
	  architecture Behavioral of mux8x1_package is
	  
	  begin
	  process(I,S)    --프로세서 구문. 
	  begin 
	  Y <= mux8x1(I,S);  --해당 패키지를 사용.
	  end process;
	  
	  end Behavioral;