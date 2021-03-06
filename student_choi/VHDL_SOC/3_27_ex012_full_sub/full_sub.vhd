library ieee;
use ieee.std_logic_1164.all;

entity full_sub is
port(x : in std_logic;
     y : in std_logic;
	  bi : in std_logic;
	  d : out std_logic;
	  bo : out std_logic);
	  end full_sub;
	  
	  architecture Structural of full_sub is
	  
	  signal temp1 : std_logic;
	  signal temp2 : std_logic;
	  signal temp3 : std_logic;
	  
	  component half_sub is
	  port(x, y : in std_logic; d, bo : out std_logic);
	  end component;
	  
	  component OR_Gate is
	  port(A,B : in std_logic;  c : out std_logic);
	  end component;
	  
	  begin
	  
	  half1 : half_sub port map (x, y, temp1, temp2);
	  half2 : half_sub port map (temp1, bi, d, temp3);
	  org : OR_Gate port map (temp2, temp3, bo);
	  
	  end Structural;