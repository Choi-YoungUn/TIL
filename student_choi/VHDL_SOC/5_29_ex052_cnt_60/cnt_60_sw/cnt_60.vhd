library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity cnt_60 is
port( nrst : in std_logic;   --리셋 신호 입력
      clk : in std_logic;     --클럭 신호 입력
		digit_ten : out std_logic_vector(3 downto 0); --십의자리 7segment
		digit_one : out std_logic_vector(3 downto 0); --일의자리 7segment
		carry : out std_logic);
		end cnt_60;
		
architecture behav of cnt_60 is

signal cnt : integer range 0 to 59;  --0~59까지 카운트
signal timeone, timeten : std_logic_vector(3 downto 0); --중간 신호

begin
 process(nrst, clk)
 begin
 if(nrst = '0')then --리셋이 0이라면
    timeone <= "0000"; --7segment = 0
	 timeten <= "0000"; --7segment = 0
	 carry <= '0';      --carry = 0
  elsif(rising_edge(clk))then  --클럭의 상승 엣지마다
    if(cnt = 59)then --카운트가 59라면
	  cnt <= 0;   --카운트 0으로 리셋
	  carry <= '1'; --캐리 1
	  timeone <= "0000"; --7segment 0으로 초기화
	  timeten <= "0000";--7segment 0으로 초기화
	  else
	  carry <= '0';  --아니라면 캐리 0
	  cnt <= cnt +1;  --카운트 1증가
	  if(timeone = 9)then --만약 일의자리가 9라면
	      timeone <= "0000"; --일의자리 0으로
			if(timeten = 5)then --만약 십의자리가 5라면
			timeten <= "0000"; --0으로 초기화
			else
			timeten <= timeten + '1'; --아니라면 십의자리 1 추가
			end if;
	    else
	      timeone <= timeone + '1'; --아니라면 일의자리 1추가
	    end if;
	    
	 end if;
 end if;
end process;
digit_one <= timeone; --7segment로 대입
digit_ten <= timeten;--7segment로 대입

end behav;
