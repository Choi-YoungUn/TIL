library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity nine_bcd is
port ( nbit : in std_logic_vector(8 downto 0);     --입력된 9비트 신호   
       bcdcord : out std_logic_vector(11 downto 0)); --변환된 BCD코드 출력
		 end nine_bcd;
		 
		 architecture behav of nine_bcd is
		 begin
		 
		 process(nbit)
		 
		 variable temp : std_logic_vector(11 downto 0); --출력될 BCD코드를 위한 변수 선언
		 variable num : integer;--10진수 변수 선언
		 
		 begin   
		 num := 0; --10진수의 초기값 '0' 입력
		 if(nbit(0) ='1') then -- 9비트중 최하위 비트가 '1'일시 10진수 변수에 1을 가산.
        num := num + 1;
		 end if;
    if(nbit(1) = '1') then -- 9비트중 2번째 비트가 '1'일시 10진수 변수에 2을 가산.
    num := num + 2;
	 end if;
       if(nbit(2) = '1') then -- 9비트중 3번째 비트가 '1'일시 10진수 변수에 4을 가산.
       num := num + 4;
		 end if;
          if(nbit(3) ='1') then -- 9비트중 4번째 비트가 '1'일시 10진수 변수에 8을 가산.
          num := num + 8;
			 end if;
             if(nbit(4) ='1') then -- 9비트중 5번째 비트가 '1'일시 10진수 변수에 16을 가산.
             num := num + 16;
				 end if;
                  if(nbit(5) ='1') then -- 9비트중 6번째 비트가 '1'일시 10진수 변수에 32을 가산.
                  num := num + 32;
						end if;
                      if(nbit(6) ='1') then -- 9비트중 7번째 비트가 '1'일시 10진수 변수에 64을 가산.
                      num := num + 64;
							 end if;
                          if(nbit(7) ='1') then -- 9비트중 8번째 비트가 '1'일시 10진수 변수에 128을 가산.
                          num := num + 128;
								  end if;
                             if(nbit(8) ='1') then -- 9비트중 9번째 비트가 '1'일시 10진수 변수에 256을 가산.
                             num := num + 256;
                             end if;
                          --10진수 변수의 최대값은 511이다.

if(num >= 500)then --변환되어 입력된 10진수가 500이상 일시 BCD코드 중 맨 위에서 네번째 자리까지 해당 코드 입력.
  temp(11 downto 8) := "0101";
  num := (num - 500);  --10진수 변수에서 500을 감산.
elsif(num >= 400) then
 temp(11 downto 8) := "0100";  --위와 같은 방식으로 100의 자리 계산.
  num := num - 400;
elsif(num >= 300) then
 temp(11 downto 8) := "0011";
  num := num - 300;
elsif(num >= 200) then
 temp(11 downto 8) := "0010";
  num := num - 200;
elsif(num >= 100) then
 temp(11 downto 8) := "0001";
  num := num - 100;
else
 temp(11 downto 8) := "0000";
end if;
         --여기까지 99이상의 숫자, 즉 100의자리 숫자를 BCD코드로 변환. 이후 10진수 변수는 무조건 두자리 수이다.
if(num >= 90) then  --변환되어 입력된 10진수가 90이상 일시 BCD코드 중 5번째 자리 부터 8번째자리까지 해당 코드 입력.
temp(7 downto 4) := "1001";
num := num-90;     --10진수 변수에서 90을 감산.
elsif(num >= 80) then
temp(7 downto 4) := "1000"; --위와 같은 방식으로 10의 자리 계산.
num := num-80;
elsif(num >= 70) then
temp(7 downto 4) := "0111";
num := num-70;
elsif(num >= 60) then
temp(7 downto 4) := "0110";
num := num-60;
elsif(num >= 50) then
temp(7 downto 4) := "0101";
num := num-50;
elsif(num >= 40) then
temp(7 downto 4) := "0100";
num := num-40;
elsif(num >= 30) then
temp(7 downto 4) := "0011";
num := num-30;
elsif(num >= 20) then
temp(7 downto 4) := "0010";
num := num-20;
elsif(num >= 10) then
temp(7 downto 4) := "0001";
num := num-10;
else
temp(7 downto 4) := "0000";
end if;
 --여기까지 9이상의 숫자, 즉 10의자리 숫자를 BCD코드로 변환. 이후 10진수 변수는 무조건 한자리 수이다.
if(num >= 9) then  --변환되어 입력된 10진수가 9이상 일시 BCD코드 중 9번째 자리부터 마지막 자리까지 해당 코드 입력.
temp(3 downto 0) := "1001";
elsif(num >= 8) then
temp(3 downto 0) := "1000";
elsif(num >= 7) then
temp(3 downto 0) := "0111";
elsif(num >= 6) then
temp(3 downto 0) := "0110";
elsif(num >= 5) then
temp(3 downto 0) := "0101";
elsif(num >= 4) then
temp(3 downto 0) := "0100";
elsif(num >= 3) then
temp(3 downto 0) := "0011";
elsif(num >= 2) then
temp(3 downto 0) := "0010";
elsif(num >= 1) then
temp(3 downto 0) := "0001";
else
temp(3 downto 0) := "0000";
end if;

bcdcord <= temp;-- 변환된 BCD코드를 출력 신호에 입력.
end process;

end behav;