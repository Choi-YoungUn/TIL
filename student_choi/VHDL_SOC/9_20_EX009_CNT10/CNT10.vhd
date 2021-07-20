library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity CNT10 is
port (reset : in std_logic;  --reset input
      clk : in std_logic;    --clk input
      start : in std_logic;
		q : out std_logic_vector(3 downto 0));  --out put
		end CNT10;
		
		architecture behav of CNT10 is
		  
		signal temp : std_logic_vector(3 downto 0);
	  signal nowstate : std_logic;
		begin
		  
     p1 : process(reset, clk)
		begin
		  if(reset = '0') then
		temp <= "0000";
		nowstate <= '0';
		  elsif (nowstate = '1') then
		  if(clk'event and clk ='1') then 
		 temp <= temp + 1;
		end if;
		  if(temp = "1010")then 
		temp <= "0000";
		nowstate <= '0';
		end if;
		  end if;
		  
		  end process;
		  
		 p2 :  process(start)
		    begin
		      if(start'event and start ='1') then
		      nowstate <= '1';
		      end if;
		      end process;
		      
		   q <= temp;
		   
		end behav;
