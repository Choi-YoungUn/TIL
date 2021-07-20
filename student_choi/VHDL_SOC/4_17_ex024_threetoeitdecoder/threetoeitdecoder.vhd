library ieee;
use ieee.std_logic_1164.all;

entity threetoeitdecoder is
port (A : in std_logic_vector(2 downto 0);
      
		Yo : out std_logic_vector(7 downto 0)
		);
		end threetoeitdecoder;
		
		architecture dataflow of threetoeitdecoder is
		begin
		Yo(7) <= A(2) and A(1) and A(0);
		Yo(6) <= A(2) and A(1) and (not A(0));
		Yo(5) <= A(2) and (not A(1)) and A(0);
		Yo(4) <= A(2) and (not A(1)) and (not A(0));
		Yo(3) <= (not A(2)) and A(1) and A(0);
		Yo(2) <= (not A(2)) and A(1) and (not A(0));
		Yo(1) <= (not A(2)) and (not A(1)) and A(0);
		Yo(0) <= (not A(2)) and (not A(1)) and (not A(0));
		end dataflow;