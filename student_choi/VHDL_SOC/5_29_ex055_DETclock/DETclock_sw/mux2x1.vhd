library ieee;
use ieee.std_logic_1164.all;

entity mux2x1 is
port (a : in std_logic;
      b : in std_logic;
		sel : in std_logic;
		y : out std_logic);
		end mux2x1;
		
		architecture dataflow of mux2x1 is
		
		begin
		with sel select
		y <= b when '1', --sel 이 1이면 b
		 a when '0',     -- 0이면 a가 나온다.
		 null when others;  --혹시 다른 동작은 무효 처리,
		 end dataflow;