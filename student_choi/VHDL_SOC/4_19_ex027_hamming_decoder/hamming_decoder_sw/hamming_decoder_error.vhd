library ieee;
use ieee.std_logic_1164.all;

entity hamming_decoder_error is
port(  syni : in std_logic_vector(2 downto 0); --신드롬

		 error : out std_logic_vector(6 downto 0)--에러코드
		 );
		 end hamming_decoder_error;
		 
		 architecture dataflow of hamming_decoder_error is
		 begin
		 error <= "1000000" when syni = "111" else
		          "0100000" when syni = "011" else
					 "0010000" when syni = "111" else
					 "0001000" when syni = "101" else
					 "0000100" when syni = "100" else
					 "0000010" when syni = "010" else
					 "0000001" when syni = "001" else
					 "0000000" when syni = "000" ;
		 
		 end dataflow;