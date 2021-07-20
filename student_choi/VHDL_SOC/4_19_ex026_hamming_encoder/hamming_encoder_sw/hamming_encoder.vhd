library ieee;
use ieee.std_logic_1164.all;


entity hamming_encoder is
port ( ai : in std_logic_vector(3 downto 0); --데이터 비트
       
		 yo : out std_logic_vector(6 downto 0) --송신 비트
		 );
		 end hamming_encoder;
		 
		 architecture dataflow of hamming_encoder is
		 begin
		 yo(6) <= ai(3);
		 yo(5) <= ai(2);
		 yo(4) <= ai(1);
		 yo(3) <= ai(0);
		 yo(2) <= ai(0) xor ai(1) xor ai(3); --페리티 비트 생성.
		 yo(1) <= ai(1) xor ai(2) xor ai(3); --페리티 비트 생성.
		 yo(0) <= ai(0) xor ai(1) xor ai(2); --페리티 비트 생성.
		 end dataflow;