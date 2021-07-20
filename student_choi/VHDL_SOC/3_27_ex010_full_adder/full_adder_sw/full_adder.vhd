library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
port (x : in std_logic;
      y : in std_logic;
		ci : in std_logic;
		s : out std_logic;
		co : out std_logic);
		end full_adder;
		
		architecture Structural of full_adder is
		
		signal temp1 : std_logic;
		signal temp2 : std_logic;
		signal temp3 : std_logic;
		
		component half_adder is
		port(x , y : in std_logic; s, c : out std_logic);
		end component;
		
		component OR_Gate is
		port(A, B : in std_logic; c : out std_logic);
		end component;
		
		begin
		
		half1 : half_adder port map(x, y, temp1, temp2);
		half2 : half_adder port map(temp1, ci, s, temp3);
		org : OR_Gate port map(temp3, temp2, co);
		
		end Structural;