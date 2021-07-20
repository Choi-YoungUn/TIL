library ieee;
use ieee.std_logic_1164.all;

entity seq_detector_four is
port(sign_in : in std_logic;     --무작위 데이터 입력
     clk : in std_logic;         --클럭
	  reset : in std_logic;       --리셋
	  data : out std_logic);      --신호감지
	  end seq_detector_four;
	  
	  architecture behav of seq_detector_four is
	  
	  type state is (s0, s1, s2, s3, s4);  --5가지 상태 설정
	  signal now_state, next_state : state;  --현재, 다음 상태 설정
	  begin
	  
	  p1 : process(clk)     --클럭에 따라
	  begin
	  if(rising_edge(clk)) then  --상승엣지시
	      if(reset = '1') then  --리셋이라면
			   now_state <= s0;  --처음상태로 
				else
				now_state <= next_state;  --아니라면 다음상태로 넘어감
				end if;
				end if;
				end process;
				
   	p2 : process(now_state, sign_in) --지금상태와 무작위 데이터에 따라
				begin
				next_state <= s0;  --초기 상태 = 첫번째 상태
				case now_state is  --현재 상태는
				when s0 =>  if (sign_in = '1') then --첫번째 상태시 무작위 데이터가 1일시 
				      next_state <= s1;   --두번째 상태로
						else
						next_state <= s0;  --아니라면 초기 상태로.
						end if;
				when s1 =>  if (sign_in = '0') then --두번째 상태시 무작위 데이터가 0일시
				      next_state <= s2;        --세번째 상태로
						else
						next_state <= s1;      --아니라면 두번째 상태 유지
						end if;
				when s2 =>  if (sign_in = '1') then  --세번째 상태시 무작위 데이터가 1일시
				      next_state <= s3;       --네번째 상태로
						else
						next_state <= s0;     --아니라면 첫번째 상태로
						end if;
				when s3 =>  if (sign_in = '1') then  --네번째 상태시 무작위 데이터가 1일시
				      next_state <= s4;     --다섯번째 상태로
						else
						next_state <= s2;     --아니라면 세번째 상태로
						end if;
				when s4 =>  if (sign_in = '1') then --네번째 상태시 무작위 데이터가 1일시
				      next_state <= s1;  --두번째 상태로
						else
						next_state <= s2;  --아니라면 세번째 상태로
						end if;
				when others => next_state <= s0;  --모든 경우가 아닐시 초기상태로
						end case;
						end process;
						
				p3 : process(now_state)
						begin
						case now_state is   --각 상태에 따른 출력 설정
						when s0 => data <= '0';
						when s1 => data <= '0';
						when s2 => data <= '0';
						when s3 => data <= '0';
						when s4 => data <= '1';  --다섯번째 즉 최종 상태시 1을 출력
						when others => data <= '0';
						end case;
						end process;
						
						end behav;