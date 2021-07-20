library ieee;
use ieee.std_logic_1164.all;

package my_mux8x1 is
      function mux8x1(input : in std_logic_vector( 7 downto 0);  -- 입력 포트.
		               sel : in std_logic_vector(2 downto 0)) --선택 포트.
							return std_logic;  --함수 선언으로 인한 리턴 자료형 선언.
	   end my_mux8x1;
							
package body my_mux8x1 is

function mux8x1(input : in std_logic_vector( 7 downto 0);   --함수 구현.
		               sel : in std_logic_vector(2 downto 0))
							return std_logic is
							variable tmp: std_logic; --변수 선언. 
							
		begin
		case sel is --sel의 값에 따라.
		when "111" => tmp := input(7);  --"111"이면 8번 입력 포트를 출력.
		when "110" => tmp := input(6);  --"110"이면 7번 입력 포트를 출력.
		when "101" => tmp := input(5);  --"101"이면 6번 입력 포트를 출력.
		when "100" => tmp := input(4);  --"100"이면 5번 입력 포트를 출력.
		when "011" => tmp := input(3);  --"011"이면 4번 입력 포트를 출력.
		when "010" => tmp := input(2);  --"010"이면 3번 입력 포트를 출력.
		when "001" => tmp := input(1);  --"001"이면 2번 입력 포트를 출력.
		when others => tmp := input(0); --이외의 값이면 1번 입력 포트를 출력.
		end case;
		
		return tmp;   --리턴 tmp.
		end mux8x1;
		
		end my_mux8x1;