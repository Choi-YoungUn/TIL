library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity sodavending_mechine is
port (coin : in std_logic_vector(1 downto 0);   --코인 입력 100원, 50원.
      reset : in std_logic;                     --초기 입력 설정...
		clk : in std_logic;                       --클럭 설정을 안하면 인식이 안댐...
      coffee : out std_logic;                   --커피 출력 가능 불.
		sevensgzero : out std_logic_vector(6 downto 0);  --0원 7세그먼트.
		sevensgten : out std_logic_vector(6 downto 0);   --50원 7세그먼트
		sevensghund : out std_logic_vector(6 downto  0)); --100원 7세그먼트
		end sodavending_mechine;
		
		architecture behav of sodavending_mechine is
		component FNDdecoder             --7세그먼트 설정
		port(data_in : in std_logic_vector(3 downto 0);
      seg : out std_logic_vector(6 downto 0));
		end component;

		type state is (s0, s1, s2, s3, s4, s5, s6); --7개의 상태 설정
		
		signal zerotosg : std_logic_vector(3 downto 0); --내부 신호
		signal tentosg : std_logic_vector(3 downto 0);
		signal hundtosg : std_logic_vector(3 downto 0);
		signal now_state, next_state : state;
		
		begin
		
		
		part1 : process(clk) --클럭에 따라 작동함.... 왜 코인에 따라는 에러가 날까...
		begin
		if(rising_edge(clk)) then --클럭의 상승 엣지시.
		   if(reset = '1') then --리셋이 1일시
		   now_state <= s0;  --초기값 = s0상태
		   else
		   now_state <= next_state; --아니라면 다음 상태로.
		   end if;
		end if;
		end process;
		
		part2 : process(now_state, coin) --지금 상태와 코인에 따라
		begin
		next_state <= s0;  --초기상태 설정.
		case now_state is
		when s0 => if(coin = "00") then  --현제 s0일시 코인입력이 없다면
		           next_state <= s0;   --현상태 유지
					  elsif(coin = "01") then --50원 입력시
					  next_state <= s1;   --s1으로 
					  elsif(coin = "10") then --100원 입력시
					  next_state <= s2;   --s2로
					  elsif(coin = "11") then --150원 동시 입력이나 동전 반환 기능으로 
					  next_state <= s0;       --생각하여 초기 값으로 이동.
					  end if;
	   when s1 => if(coin = "00") then--현제 s1일시 코인입력이 없다면
		           next_state <= s1;--현상태 유지
					  elsif(coin = "01") then--50원 입력시
					  next_state <= s2; --s2으로
					  elsif(coin = "10") then--100원 입력시
					  next_state <= s3;--s3으로
					  elsif(coin = "11") then--150원 동시 입력이나 동전 반환 기능으로
		           next_state <= s1;--생각하여 초기 값으로 이동.
					  end if;
		when s2 => if(coin = "00") then--현제 s2일시 코인입력이 없다면
		           next_state <= s2;--현상태 유지
					  elsif(coin = "01") then--50원 입력시
					  next_state <= s3;--s3으로
					  elsif(coin = "10") then--100원 입력시
					  next_state <= s4;--s4으로
					  elsif(coin = "11") then--150원 동시 입력이나 동전 반환 기능으로
		           next_state <= s2;--생각하여 초기 값으로 이동.
					  end if;
		when s3 => if(coin = "00") then--현제 s3일시 코인입력이 없다면
		           next_state <= s3;--현상태 유지
					  elsif(coin = "01") then--50원 입력시
					  next_state <= s4;--s4으로
					  elsif(coin = "10") then--100원 입력시
					  next_state <= s5;--s5으로
					  elsif(coin = "11") then--150원 동시 입력이나 동전 반환 기능으로
		           next_state <= s3;--생각하여 초기 값으로 이동.
					  end if;
		when s4 => if(coin = "00") then--현제 s4일시 코인입력이 없다면
		           next_state <= s4;--현상태 유지
					  elsif(coin = "01") then--50원 입력시
					  next_state <= s5;--s5으로
					  elsif(coin = "10") then--100원 입력시
					  next_state <= s6;--s6으로
					  elsif(coin = "11") then--150원 동시 입력이나 동전 반환 기능으로
		           next_state <= s4;--생각하여 초기 값으로 이동.
					  end if;
		when s5 => if(coin = "00") then--커피를 뽑았다고 의미한다
		           next_state <= s0;  --초기상태로 이동
					  else
					  next_state <= s5;--나머지 상태 입력시 현상태 유지
					  end if;
	   when s6 => if(coin = "00") then--커피를 뽑았다고 의미한다
		           next_state <= s1; --50원 있는 상태로 이동
					  else
					  next_state <= s6;--나머지 상태 입력시 현상태 유지
					  end if;
		end case;
		end process;
		

		part3 : process(now_state) --현재 상태에 따라서
		begin
		case now_state is
		when s0 => zerotosg <= "0000"; --각 7세그먼트의 출력 결정
		           tentosg <= "0000";
					  hundtosg <= "0000";
					   coffee <= '0'; --커피 출력 가능 상태 설정
					  
	   when s1 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0101";
					  hundtosg <= "0000";
					   coffee <= '0';--커피 출력 가능 상태 설정
					  
		when s2 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0000";
					  hundtosg <= "0001";
					   coffee <= '0';--커피 출력 가능 상태 설정
					  
	   when s3 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0101";
					  hundtosg <= "0001";
					   coffee <= '0';--커피 출력 가능 상태 설정
					  
	   when s4 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0000";
					  hundtosg <= "0010";
					   coffee <= '0';--커피 출력 가능 상태 설정
					  
		when s5 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0101";
					  hundtosg <= "0010";
					   coffee <= '1';--커피 출력 가능 상태 설정
					  
		when s6 => zerotosg <= "0000";--각 7세그먼트의 출력 결정
		           tentosg <= "0000";
					  hundtosg <= "0011";
					   coffee <= '1';--커피 출력 가능 상태 설정
					  
					  end case;
					  end process;
					  
					  
		zero : FNDdecoder      --7세그먼트로 데이터 전송 후 출력 
		port map(data_in => zerotosg, seg => sevensgzero);
		ten : FNDdecoder 
		port map(data_in => tentosg, seg => sevensgten);
		hund : FNDdecoder 
		port map(data_in => hundtosg, seg => sevensghund);
		
	 end behav;