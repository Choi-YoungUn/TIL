library ieee;
use ieee.std_logic_1164.all;
use work.my_mux8x1.all;

entity mux8x1_package is
port(I : in std_logic_vector(7 downto 0);
     S : in std_logic_vector(2 downto 0);
	  Y : out std_logic);
	  end mux8x1_package;
	  
	  architecture Behavioral of mux8x1_package is
	  
	  begin
	  process(I,S)
	  begin 
	  Y <= mux8x1(I,S);
	  end process;
	  
	  end Behavioral;