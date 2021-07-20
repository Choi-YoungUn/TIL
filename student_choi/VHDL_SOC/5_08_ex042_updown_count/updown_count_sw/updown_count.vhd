library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all; --연산하기 위한 라이브러리

entity updown_count is
port( reset : in std_logic;  --reset input
      clk : in std_logic;    --clk input
		up_down : in std_logic;  --up or down sign input
		q : out std_logic_vector(3 downto 0)); --out put
		end updown_count;
		
		architecture behav of updown_count is
		
		signal temp : std_logic_vector(3 downto 0); --내부 신호 설정
		
		begin 
		process(reset, clk)
		begin
		if (reset = '1') then   --reset시 값은 "0000"
		temp <= "0000";
		elsif ( clk'event and clk = '1')then  --clk = 상승엣지시
		 if (up_down = '1') then -- up sign 시 
		   temp <= temp + '1';  --상승 카운터
			else
			temp <= temp - '1';  --down sign 시   하강 카운터.
			end if;
			end if;
	   end process;
		q <= temp;
			end behav;
		