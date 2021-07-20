library ieee;
use ieee.std_logic_1164.all;

entity twobitcomparator is
     port ( A : in std_logic_vector (1 downto 0);
	         B : in std_logic_vector (1 downto 0);
				
				XO : out std_logic;
				yo : out std_logic;
				zo : out std_logic);
				end twobitcomparator;
				
architecture Dataflow of twobitcomparator is
				
	begin
				
			XO <=( A(0) and (not B(0)) and (not B(1)) ) or ( A(1) and (not B (1)) ) or (A(1) and A(0) and (not B(0)));
			YO <=( A(0) xnor B(0) ) and ( A(1) xnor B(1) );
			zo <=( (not A(1)) and B(1) ) or ( (not A(1)) and (not A (0)) and B(0) ) or ( (not A(0)) and B(1) and B(0) );
				
	end Dataflow;