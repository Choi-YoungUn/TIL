library ieee;
use ieee.std_logic_1164.all;

entity hamming_decoder_syn is
port( ai : in std_logic_vector(6 downto 0); --입력 헤밍 코트

       syn : out std_logic_vector(2 downto 0)--신드롬(해석코드)
		 );
		 end hamming_decoder_syn;
		 
		 architecture dataflow of hamming_decoder_syn is
		 begin
		 
		 syn(2) <= ai(3) xor ai(4) xor ai(6) xor ai(2);
		 syn(1) <= ai(4) xor ai(5) xor ai(6) xor ai(1);
		 syn(0) <= ai(3) xor ai(4) xor ai(5) xor ai(0);
		 
		 end dataflow;