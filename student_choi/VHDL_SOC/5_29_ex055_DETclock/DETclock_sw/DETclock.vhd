library ieee;
use ieee.std_logic_1164.all;

entity DETclock is
port( nrst : in std_logic;    --각종 입력에 대한 선언들.
      clk : in std_logic;
		key_sec : in std_logic;
		key_min : in std_logic;
		key_hor : in std_logic;
		sel_sw : in std_logic;
		
		fnd_sec_ten : out std_logic_vector(6 downto 0);  --각종 아웃 신호에 대한 선언들
		fnd_sec_one : out std_logic_vector(6 downto 0);  
		fnd_min_ten : out std_logic_vector(6 downto 0);
		fnd_min_one : out std_logic_vector(6 downto 0);
		fnd_hor_ten : out std_logic_vector(6 downto 0);
		fnd_hor_one : out std_logic_vector(6 downto 0));
		end DETclock;
		
		architecture struc of DETclock is
		
	component sec_gen is  -- 클럭을 초단위로 만든다.
port( nrst : in std_logic;
      clk : in std_logic;
		sec_sig : out std_logic);
		end component;
		
	component	FNDdecoder is   --2진수 코드를 7segment로 표현하게 해준다
port (data_in : in std_logic_vector(3 downto 0);
      seg : out std_logic_vector(6 downto 0));
		end component;
		
	component	mux2x1 is  --시간을 조정 할때 덧셈 해주는 역할.
port (a : in std_logic; 
      b : in std_logic;
		sel : in std_logic;  
		y : out std_logic);
		end component;
		
	component cnt_60 is
port( nrst : in std_logic;   --리셋 신호 입력
      clk : in std_logic;     --클럭 신호 입력
		digit_ten : out std_logic_vector(3 downto 0); --십의자리 7segment
		digit_one : out std_logic_vector(3 downto 0); --일의자리 7segment
		carry : out std_logic);
		end component;
		
	component	cnt_24 is
port( nrst : in std_logic;   --리셋 신호 입력
      clk : in std_logic;     --클럭 신호 입력
		digit_ten : out std_logic_vector(3 downto 0); --십의자리 7segment
		digit_one : out std_logic_vector(3 downto 0)); --일의자리 7segment
		end component;
		
		signal sec_sign : std_logic := '0';    --중간 신호 연결 선 설정.
		signal sec_clk : std_logic := '0'; 
		signal min_clk : std_logic := '0';
		signal hor_clk : std_logic := '0';
		signal sec_carry : std_logic := '0';
		signal min_carry : std_logic := '0';
		signal sec_cnt_ten : std_logic_vector(3 downto 0) := "0000";
		signal sec_cnt_one : std_logic_vector(3 downto 0) := "0000";
		signal min_cnt_ten : std_logic_vector(3 downto 0) := "0000";
		signal min_cnt_one : std_logic_vector(3 downto 0) := "0000";
		signal hor_cnt_ten : std_logic_vector(3 downto 0) := "0000";
		signal hor_cnt_one : std_logic_vector(3 downto 0) := "0000";
		
		begin
		               --클럭 밑 신호 분주
		s_sec_gen : sec_gen  --클럭을 1초로 환산해 주는 프로그램
		port map(nrst => nrst, clk => clk, sec_sig => sec_sign);
		-- mux 
		m_sec_mux : mux2x1  -- 1초를 덧셈하기 위한 MUX
		port map(a => sec_sign, b => key_sec, sel => sel_sw, y => sec_clk);
		m_min_mux : mux2x1  -- 1분를 덧셈하기 위한 MUX
		port map(a => sec_carry, b => key_min, sel => sel_sw, y => min_clk);
		m_hor_mux : mux2x1  -- 1시간을 덧셈하기 위한 MUX
		port map(a => min_carry, b => key_hor, sel => sel_sw, y => hor_clk);
		                --시간으로 변환
		six_cnt_sec : cnt_60  --60초를 카운트 하여 60이 되면 1분을 추가
		port map(nrst => nrst, clk => sec_clk, digit_ten => sec_cnt_ten,
		         digit_one => sec_cnt_one, carry => sec_carry);
		six_cnt_min : cnt_60 --60분를 카운트 하여 60이 되면 1시간을 추가
		port map(nrst => nrst, clk => min_clk, digit_ten => min_cnt_ten,
		         digit_one => min_cnt_one, carry => min_carry);
		two_cnt_hor : cnt_24 --24시간를 카운트 하여 24시가 되면 모든 시간 0시 0분 0초
		port map(nrst => nrst, clk => hor_clk, digit_ten => hor_cnt_ten,
		         digit_one => hor_cnt_one);
		              --fnd 7segment
		f_fnd_sec_one : FNDdecoder  --각 시 분 초를 7SEgment로 디스플레이 하기위함
		port map(data_in => sec_cnt_one, seg => fnd_sec_one);
		f_fnd_sec_ten : FNDdecoder
		port map(data_in => sec_cnt_ten, seg => fnd_sec_ten);
		f_fnd_min_one : FNDdecoder
		port map(data_in => min_cnt_one, seg => fnd_min_one);
		f_fnd_min_ten : FNDdecoder
		port map(data_in => min_cnt_ten, seg => fnd_min_ten);
		f_fnd_hor_one : FNDdecoder
		port map(data_in => hor_cnt_one, seg => fnd_hor_one);
		f_fnd_hor_ten : FNDdecoder
		port map(data_in => hor_cnt_ten, seg => fnd_hor_ten);
		
		end struc;