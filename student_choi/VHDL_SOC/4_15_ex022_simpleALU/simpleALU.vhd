library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity simpleALU is
port( A : in std_logic_vector(3 downto 0);
      B : in std_logic_vector(3 downto 0);
		S : in std_logic_vector(1 downto 0);
		
		Y : out std_logic_vector(4 downto 0)
		);
		end simpleALU;
		
		architecture simple of simpleALU is
		 component half_adder is
		port ( a : in std_logic;
          b : in std_logic;
          s : out std_logic;
          co : out std_logic);
end half_adder;

       component full_adder is
      port (a : in std_logic;
      b : in std_logic;
		ci : in std_logic;
		s : out std_logic;
		co : out std_logic);
		end full_adder;
		
		signal carry0 : std_logic;
		