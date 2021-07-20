library ieee;
use ieee.std_logic_1164.all;

entity eittothreeencoder is
port ( A : in std_logic_vector(7 downto 0);
       
		 Yo: out std_logic_vector(2 downto 0)
		 );
		 end eittothreeencoder;
		 
		 architecture Dataflow of eittothreeencoder is
		 begin
		 Yo(0) <= A(1) or A(3) or A(5) or A(7);
		 Yo(1) <= A(2) or A(3) or A(6) or A(7);
		 Yo(2) <= A(4) or A(5) or A(6) or A(7);
		 end dataflow;