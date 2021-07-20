library ieee;
use ieee.std_logic_1164.all;

entity eitbit_shift_regiDFF is
port ( data : in std_logic;
       set : in std_logic;
       rset : in std_logic;
		 clk : in std_logic;
		 q : out std_logic_vector(7 downto 0));
		 end eitbit_shift_regiDFF;
		 
		 architecture behav of eitbit_shift_regiDFF is
		 
		 signal temp : std_logic_vector(7 downto 0);
		 
		 component D_FF is
		 port (D : in std_logic;
	   clk : in std_logic;
	   preset : in std_logic;
	   clear : in std_logic;
	   Q : out std_logic);
		end component;
		
		begin
		shif0 : D_FF
		port map(D => data, clk => clk, preset => set, clear => rset, Q => temp(0));
		shif1 : D_FF
		port map(D => temp(0), clk => clk, preset => set, clear => rset, Q => temp(1));
		shif2 : D_FF
		port map(D => temp(1), clk => clk, preset => set, clear => rset, Q => temp(2));
		shif3 : D_FF
		port map(D => temp(2), clk => clk, preset => set, clear => rset, Q => temp(3));
		shif4 : D_FF
		port map(D => temp(3), clk => clk, preset => set, clear => rset, Q => temp(4));
		shif5 : D_FF
		port map(D => temp(4), clk => clk, preset => set, clear => rset, Q => temp(5));
		shif6 : D_FF
		port map(D => temp(5), clk => clk, preset => set, clear => rset, Q => temp(6));
		shif7 : D_FF
		port map(D => temp(6), clk => clk, preset => set, clear => rset, Q => temp(7));
		
		q <= temp(7 downto 0);
		end behav;