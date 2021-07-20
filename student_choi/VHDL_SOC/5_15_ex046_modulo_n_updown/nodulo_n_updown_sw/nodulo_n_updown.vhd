library ieee;
use ieee.std_logic_1164.all;

entity nodulo_n_updown is
port( clk : in std_logic;    --클럭
      reset : in std_logic;   --리셋
		updown : in std_logic;   --업/다운 설정 입력
		y : out std_logic_vector(2 downto 0));  --데이터 출력
		end nodulo_n_updown;
		
		architecture behav of nodulo_n_updown is
		 
		type state_type is ( s0, s1, s2, s3, s4, s5); --상태 타입 설정
		signal state : state_type; --상태 설정
		
		begin
		process(clk, reset) --클럭과 리셋에 따라
		begin
		if(reset = '1') then  --리셋이 1이라면
		state <= s0;  --현재상태는 초기상채(첫번째 상태)
		elsif(clk'event and clk = '1') then --클럭에 따라서
		
		case state is --현재상태가
		when s0 => if updown = '1' then  --s0일때 up 상태라면 
		        state <= s1;    --s1으로
				  else
				  state <= s5;   --아니라면 s5로 
				  end if;
		when s1 => if updown = '1' then  --s1일때 up 상태라면 
		        state <= s2;    --s2으로
				  else
				  state <= s0;   --아니라면 s0로
				  end if;
				  
		when s2 => if updown = '1' then  --s2일때 up 상태라면 
		        state <= s3;    --s3으로
				  else
				  state <= s1;   --아니라면 s1로
				  end if;
				  
	   when s3 => if updown = '1' then  --s3일때 up 상태라면 
		        state <= s4;    --s4으로
				  else
				  state <= s2;   --아니라면 s2로
				  end if;
				  
	   when s4 => if updown = '1' then  --s4일때 up 상태라면 
		        state <= s5;    --s5으로
				  else
				  state <= s3;   --아니라면 s3로
				  end if;
				  
	   when s5 => if updown = '1' then  --s5일때 up 상태라면 
		        state <= s0;    --s0으로
				  else
				  state <= s4;   --아니라면 s4로
				  end if;
				  end case;
				  end if;
				  end process;
				  
				  y <= "000" when (state = s0) else  --각 상태에 따른 출력 값 설정
				       "001" when (state = s1) else
						 "010" when (state = s2) else
						 "011" when (state = s3) else
						 "100" when (state = s4) else
						 "101";
						 end behav;