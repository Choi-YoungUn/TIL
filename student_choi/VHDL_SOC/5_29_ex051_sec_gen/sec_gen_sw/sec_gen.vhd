library ieee;
use ieee.std_logic_1164.all;

entity sec_gen is
port( nrst : in std_logic;
      clk : in std_logic;
		sec_sig : out std_logic);
		end sec_gen;
		
		architecture behav of sec_gen is
		
		signal cnt : integer range 0 to 24999999;
		signal sig : std_logic;
		
		begin
		
		process(nrst, clk)
		begin
		if(nrst = '0') then
		cnt <= 0;
		sig <= '0';
		elsif(clk'event and clk = '1') then
		if(cnt = 24999999) then
		--2499로 변경해서 시뮬 확인.
		cnt <= 0;
		sig <= not(sig);
		else
		cnt <= cnt +1;
		end if;
		end if;
		end process;
		
		sec_sig <= sig;
		end behav;