library ieee;
use ieee.std_logic_1164.all;
use work.my_demux1x8.all;    --패키지 라이브러리.

entity demux1x8_pack_proce is   
    port (I : in std_logic; --하나의 입력 포트.
	       S : in std_logic_vector(2 downto 0);  --선택포트  
	       Y : out std_logic_vector(7 downto 0));  -- 출력 포트.
	 end demux1x8_pack_proce;
	 
	 architecture Behavioral of demux1x8_pack_proce is
	 
	 begin
	     process(I,S)  
		  begin
		  demux1x8_proce(I,S,Y);  --패키지 활용 선언.
		  end process;
		  
		  end Behavioral;
	 
	 