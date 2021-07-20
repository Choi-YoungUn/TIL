library ieee;
use ieee.std_logic_1164.all;


entity onebitfullcomparator_vh is   --한비트 비교기 
port ( A : in std_logic;   --입력 신호A
       B : in std_logic;    --입력 신호B
		 Xi : in std_logic;   --이전 신호(하위 값이 A > B)
		 Yi : in std_logic;   --이전 신호(하위 값이 A = B)
		 Zi : in std_logic;   --이전 신호(하위 값이 A < B)
		 
		 Xo : out std_logic;  --A > B
		 Yo : out std_logic;  --A = B
		 Zo : out std_logic); --A < B
		 end onebitfullcomparator_vh;
		 
		 architecture behav of onebitfullcomparator_vh is
		 begin
		  process(A , B, xi, yi, zi) --순차적으로 하기위한 선언
		  begin
		   if(A > B) then  --A > B 라면
			xo <= '1';  --XO 가 '1'
			yo <= '0';
			zo <= '0';
			end if;
			if(A < B) then  --A < B 라면
			xo <= '0';  --ZO 가 '1'
			yo <= '0';
			zo <= '1';
			end if;
			if(A = B) then  --A = B 라면
			  if(xi = '1') then  --XI = '1'일때
			   xo <= '1';   --XO 가 '1'
			   yo <= '0';
			   zo <= '0';
			  end if;
			  if(yi = '1') then  --YI = '1'일때
			   xo <= '0';
			   yo <= '1';    --YO 가 '1'
			   zo <= '0';
				end if;
			  if(zi = '1') then  --ZI = '1'일때
			   xo <= '0';
			   yo <= '0';   
			   zo <= '1';    --ZO 가 '1
				end if;
				end if;
			end process;
		  
		  
		  end behav;
		 
		 