library ieee;
use ieee.std_logic_1164.all;

entity eitbit_par_register is
port( rset : in std_logic; --reset in put
      en : in std_logic; --enable signal in put
		clk : in std_logic; --clk in put
		data : in std_logic_vector(7 downto 0); --data in put
		q : out std_logic_vector(7 downto 0)); --출력 out put
		end eitbit_par_register;
		
		architecture behav of eitbit_par_register is
		
	begin 
	
	process(rset, en, clk)
	begin
	if(rset = '1') then  --reset = '1' 시 
	q <= "00000000";  --출력 = "00000000"
	elsif(en = '1') then  -- enable 신호 입력시
	if(clk'event and clk = '1') then --클럭의 상승 엣지 일때
	q <= data; --데이터가 8비트 그대로 출력 된다.
	end if;
	end if;
	
	end process;
	
	end behav;