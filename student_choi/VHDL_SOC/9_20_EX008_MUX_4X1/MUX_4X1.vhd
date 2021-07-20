library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity mux_4x1 is
port(
   A : in std_logic;
   B : in std_logic;
   C : in std_logic;
   D : in std_logic;
   SEL : in std_logic_vector(1 downto 0);
   
   Y : out std_logic
   );
   end mux_4x1;
   
   architecture BEH of mux_4x1 is
   begin
   Y <= A when SEL = 0 else
        B when SEL = 1 else
        C when SEL = 2 else
        D when SEL = 3 else
        'Z';
        end BEH;
        
   