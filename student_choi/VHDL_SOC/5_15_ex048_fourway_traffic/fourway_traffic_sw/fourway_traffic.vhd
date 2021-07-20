library ieee;
use ieee.std_logic_1164.all;

entity fourway_traffic is
port ( clk : in std_logic;    --input clk
       reset : in std_logic;     --reset input
		 e_w_red : out std_logic;     --동서 빨간불
		 e_w_yellow : out std_logic;   --동서 노란불
		 e_w_green : out std_logic;    --동서 초록불
		 n_s_red : out std_logic;      --남북 빨간불
		 n_s_yellow : out std_logic;   --남북 노란불
		 n_s_green : out std_logic);   --남북 초록불
		 end fourway_traffic;
		 
		 architecture behav of fourway_traffic is
		 
		 type state is (s0, s1, s2, s3, s4, s5);  --전체 경우의 수 설정
		 
		 constant time_green : integer := 5;  --초록불시 유지시간
		 constant time_red : integer := 2;    --빨간불시 유지시간(단 남북 신호가 끝났을 때)
		 constant time_yellow : integer := 2;  --노란불시 유지시간
		 constant time_end : integer := 3;    --빨간불시 유지시간(단 동서 신호가 끝났을 때)
		 
		 signal now_state, next_state: state;  --현재상태와 다음상태 설정
		 signal time_setting : integer range 0 to 5; --시간 설정 0~5
		 
		 begin  
		 p1 : process(reset, clk)  --전체 시퀀스. 
		   variable count : integer range 0 to 5;  --동작하는 시간
			begin
			if(reset = '1')then   --리셋시 둘다 빨간불
			now_state <= s5;
			elsif(clk'event and clk = '1')then  --클럭 발생(시간 흐름)
			count := count + 1;  --시간을 하나씩 덧셈.
			if (count = time_setting)then --만약 셋팅된 시간과 같다면 다음 상태로 넘어감
			now_state <= next_state ;
			count := 0; --시간 카운트 다시 0으로 리셋
			end if;
			end if;
			end process;
			
			p2 : process(now_state)
			begin
			   case now_state is  --현재 상태를 기준으로
			when s0 =>  e_w_red <= '0';      --첫번째 상태시  
		               e_w_yellow <= '0';       --동서 초록불
						   e_w_green <= '1';
							n_s_red <= '1';         --남북 빨간불
		               n_s_yellow <= '0';
						   n_s_green <= '0';
							time_setting <= time_green ;  --초록불 5초지연
							next_state <= s1;    --다음상태 설정
			when s1 =>  e_w_red <= '0';     --두번째 상태시
		               e_w_yellow <= '1';   --동서 노란불
					  	   e_w_green <= '0';
							n_s_red <= '1';     --남북 빨간불 유지
		               n_s_yellow <= '0';
						   n_s_green <= '0';
						   time_setting <= time_yellow ;  --노란불 2초지연
						   next_state <= s2; --다음상태 설정
			when s2 =>  e_w_red <= '1';   --세번째 상태
		               e_w_yellow <= '0';   --동서 빨간불
					  	   e_w_green <= '0';
							n_s_red <= '1';     --남북 빨간불
		               n_s_yellow <= '0';
						   n_s_green <= '0';
						   time_setting <= time_red ;    --빨간불 2초지연
						   next_state <= s3;   --다음상태 설정
			when s3 =>  e_w_red <= '1';    --네번째 상태
		               e_w_yellow <= '0';      --동서 빨간불
					  	   e_w_green <= '0';
							n_s_red <= '0';
		               n_s_yellow <= '0';
						   n_s_green <= '1';
						   time_setting <= time_green;  --초록불 5초지연
						   next_state <= s4;   --다음상태 설정
			when s4 =>  e_w_red <= '1';      --다섯번째 상태
		               e_w_yellow <= '0';      --동서 빨간불
					  	   e_w_green <= '0';
							n_s_red <= '0';
		               n_s_yellow <= '1';
						   n_s_green <= '0';
						   time_setting <= time_yellow;  --노란불 2초지연
						   next_state <= s5;   --다음상태 설정
      	when s5 =>  e_w_red <= '1';     --여섯번째 상태
		               e_w_yellow <= '0';      --동서 빨간불
					  	   e_w_green <= '0';
							n_s_red <= '1';    --남북 빨간불
		               n_s_yellow <= '0';
						   n_s_green <= '0';
						   time_setting <= time_end; --빨간불 단 전체 상태 끝이므로 3초지연
						   next_state <= s0;   --다음상태 설정
			end case;
			end process;
			
			end behav;
			