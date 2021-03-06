library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity ring_counter is
port ( reset : in std_logic;
       clk : in std_logic;
		 q : out std_logic_vector(3 downto 0));
		 end ring_counter;
		 
		 architecture behav of ring_counter is
		 component D_FF is
port (D : in std_logic;
	   clk : in std_logic;
	   clear : in std_logic;
	   Q : out std_logic);
		end component;	 
		 
		 signal temp : std_logic_vector(3 downto 0);
		 
		 begin
		 
		 d0 : D_FF
		 port map(D => temp(3), clk => clk, clear => reset, q => temp(0));
		 d1 : D_FF
		 port map(D => temp(0), clk => clk, clear => reset, q => temp(1));
		 d2 : D_FF 
		 port map(D => temp(1), clk => clk, clear => reset, q => temp(2));
		 d3 : D_FF
		 port map(D => temp(2), clk => clk, clear => reset, q => temp(3));
		if(temp ="0000")then
		 temp(0) <='1';
		 end if;
		q<= temp;
		
		 end behav;