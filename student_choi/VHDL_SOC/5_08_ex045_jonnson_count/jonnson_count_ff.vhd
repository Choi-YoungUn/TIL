library ieee;
use ieee.std_logic_1164.all;

entity jonnson_count_ff is
port ( reset : in std_logic;  --reset input
       clk : in std_logic;  --clk input
		 q : out std_logic_vector(3 downto 0)); --out put
		 end jonnson_count_ff;
		
		architecture behav of jonnson_count_ff is
		component D_FF is
     port (D : in std_logic;
	   clk : in std_logic;
	   clear : in std_logic;
	   Q : out std_logic);
		end component;
		
		signal temp : std_logic_vector(3 downto 0);
		begin
		
		d0 : D_FF
		port map(D => temp(3),clk => clk, clear => reset, Q => temp(0));
		d1 : D_FF
		port map(D => temp(0),clk => clk, clear => reset, Q => temp(1));
		d2 : D_FF
		port map(D => temp(1),clk => clk, clear => reset, Q => temp(2));
		d3 : D_FF
		port map(D => temp(2),clk => clk, clear => reset, Q => temp(3));
		 q <= temp;
		end behav;