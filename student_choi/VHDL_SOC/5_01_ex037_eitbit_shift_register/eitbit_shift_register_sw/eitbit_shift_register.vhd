library ieee;
use ieee.std_logic_1164.all;

entity eitbit_shift_register is
port ( rset : in std_logic;  --reset in put
       clk : in  std_logic;  --clk in put
		 data : in std_logic;  --data in put
		 q : out std_logic_vector(7 downto 0)); --출력 
		 end eitbit_shift_register;
		 
		 architecture behav of eitbit_shift_register is
		 signal temp : std_logic_vector(7 downto 0); --신호 선언
		 
		 begin
		 process(rset, clk)
		 begin
		 if(rset = '1') then --reset = '1' 일때
		 temp <= "00000000"; --출력  = "00000000"
		 elsif(clk'event and clk = '1') then --클럭이 상승엣지일 때
		 temp <= temp(6 downto 0) & data; --데이터가 한비트씩 상위 비트로 이동.
		 end if;         --최하위 비트는 데이터 입력을 받음.
		 end process;
		 
		 q <= temp;
		 
		 end behav;