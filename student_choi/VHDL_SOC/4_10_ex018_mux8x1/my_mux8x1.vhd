library ieee;
use ieee.std_logic_1164.all;

package my_mux8x1 is
      function mux8x1(input : in std_logic_vector( 7 downto 0);
		               sel : in std_logic_vector(2 downto 0))
							return std_logic;
	   end my_mux8x1;
							
package body my_mux8x1 is

function mux8x1(input : in std_logic_vector( 7 downto 0);
		               sel : in std_logic_vector(2 downto 0))
							return std_logic is
							variable tmp: std_logic;
							
		begin
		case sel is
		when "111" => 
			tmp := input(7);
		when "110" => tmp := input(6);
		when "101" => tmp := input(5);
		when "100" => tmp := input(4);
		when "011" => tmp := input(3);
		when "010" => tmp := input(2);
		when "001" => tmp := input(1);
		when others => tmp := input(0);
		end case;
		
		return tmp;
		end mux8x1;
		
		end my_mux8x1;