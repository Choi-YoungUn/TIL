library ieee;
use ieee.std_logic_1164.all;

entity fourbit_non_twoup_count_sw is
port( clk : in std_logic;    --클럭 입력
      reset : in std_logic;   --리셋
		q : out std_logic_vector(3 downto 0));  --출력
		end fourbit_non_twoup_count_sw;
		
		architecture behav of fourbit_non_twoup_count_sw is
		
		component JK_FF 
		port( j : in std_logic;   --SET INPUT
      k : in std_logic;   --RESET INPUT
		clk : in std_logic;  --클럭 INPUT
		clr : in std_logic; --clear in put
		q :out std_logic);    --출력 파형
		end component;
		
		signal temp : std_logic_vector(3 downto 0);
		
		begin
		jk1 : jk_FF
		port map (j => '1', k => '1', clk => clk, clr => reset, q => temp(0));  --첫째 FF단
		jk2 : jk_FF
		port map (j => '1', k => '1', clk => temp(0), clr => reset, q => temp(1));--둘째 FF단
		jk3 : jk_FF
		port map (j => '1', k => '1', clk => temp(1), clr => reset, q => temp(2));--셋째 FF단
		jk4 : jk_FF
		port map (j => '1', k => '1', clk => temp(2), clr => reset, q => temp(3));--넷째 FF단
		
		q <= temp;    --출력
		end behav;