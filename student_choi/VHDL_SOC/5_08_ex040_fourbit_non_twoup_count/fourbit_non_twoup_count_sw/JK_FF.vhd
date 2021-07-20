library ieee;
use ieee.std_logic_1164.all;

entity JK_FF is
port( j : in std_logic;   --SET INPUT
      k : in std_logic;   --RESET INPUT
		clk : in std_logic;  --클럭 INPUT
		clr : in std_logic; --clear in put
		q :out std_logic);    --출력 파형
		end JK_FF;
		
		architecture behav of JK_FF is
		
		 signal temp : std_logic;  --신호 정의	 
		 begin
		 process(clk, clr)
		 begin
		 if(clr = '1') then --clear '1'일시 출력 q = '0'
		 temp <= '0';
		 elsif(clk'event and clk = '0') then --클럭이 하강 엣지일 때
		 if(j = '0' and k = '0') then --j = '0', k = '0' 일시
		 temp <= temp;  --그대로 출력(기존 유지)
		 elsif(j = '1' and k = '0') then--j = '1', k = '0' 일시
		 temp <= '1';  -- q = '1', q_ber = '0'
		 elsif(j = '0' and k = '1') then--j = '0', k = '1'일시
		 temp <= '0';  --q = '0' , q_ber = '1'
		 elsif(j = '1' and k = '1') then --j = '1', k = '1' 일시
		 temp <= not temp; --기존 출력에서 반전되어 출력
		 end if;
		 end if;
		 end process; 
		 
		 q <= temp; 	 
		 end behav;