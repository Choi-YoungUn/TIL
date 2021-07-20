library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity TB_CNT10 is end;

		architecture behav of TB_CNT10 is
		  component CNT10 is
		    port (reset : in std_logic;  --reset input
      clk : in std_logic;    --clk input
      start : in std_logic;
		q : out std_logic_vector(3 downto 0)  --out put
		);
		end component;
		
		signal reset : std_logic;
		signal clk : std_logic;
		signal start : std_logic;
		signal q : std_logic_vector(3 downto 0 );
		
		signal int_cnt : std_logic_vector(99 downto 0);
		
		begin
		  
		  process
		    begin
		      if(NOW = 0ns) then
		      reset <= '0', '1' after 200ns;
		      end if;
		      wait for 1sec;
		      end process;
		      
		      process
		        begin 
		          clk <= '0', '1' after 5 ns;
		          wait for 10ns;
		          end process;
		          
		          process(reset, clk)
		            begin
		              if(reset = '0') then
		              int_cnt <= (others => '0');
		              elsif rising_edge(clk) then
		                int_cnt <= int_cnt +1;
		                end if;
		                end process;
		                
		                start <= '1' when int_cnt = 300 or
		                                  int_cnt = 600 else
		                                  '0';
		  U_CNT10 : CNT10
		  port map(
		    reset => reset,
		    clk => clk,
		    start => start,
		    q => q);
		   
		end behav;
