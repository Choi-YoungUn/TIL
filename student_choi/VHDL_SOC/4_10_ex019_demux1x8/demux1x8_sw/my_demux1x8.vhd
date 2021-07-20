library ieee;
use ieee.std_logic_1164.all;

package my_demux1x8 is      --PROCEDURE선언
    procedure demux1x8_proce (signal I : in std_logic;  --입력 포트.
	 signal S : in std_logic_vector(2 downto 0);   --선택 포트
	 signal O : out std_logic_vector(7 downto 0));   --출력 포트
	 end my_demux1x8;
	 
	 package body my_demux1x8 is
	 
	 procedure demux1x8_proce (signal I : in std_logic;   --PROCEDURE 정의   
	 signal S : in std_logic_vector(2 downto 0);
	 signal O : out std_logic_vector(7 downto 0)) is
	 
	 begin      
	 case S is   -- procedure 구현
	 when "111"  => O <=      I & "0000000";  -- S = "111"시 O(7)에 입력값을 출력
	 when "110"  => O <= '0' & I & "000000";  -- S = "110"시 O(6)에 입력값을 출력
	 when "101"  => O <= "00" & I & "00000";  -- S = "101"시 O(5)에 입력값을 출력
	 when "100"  => O <= "000" & I & "0000";  -- S = "100"시 O(4)에 입력값을 출력
	 when "011"  => O <= "0000" & I & "000";  -- S = "011"시 O(3)에 입력값을 출력
	 when "010"  => O <= "00000" & I & "00";  -- S = "010"시 O(2)에 입력값을 출력
	 when "001"  => O <= "000000" & I & '0';  -- S = "001"시 O(1)에 입력값을 출력
	 when others => O <= "0000000" & I     ;  -- 그외 상황 시 O(0)에 입력값을 출력
	 end case;
	 end demux1x8_proce;
	 
	 end my_demux1x8;
	 