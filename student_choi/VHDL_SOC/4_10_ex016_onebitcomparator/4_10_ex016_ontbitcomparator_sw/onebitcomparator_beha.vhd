library ieee;
use ieee.std_logic_1164.all;

entity onebitcomparator_beha is
port ( A : in std_logic; 
       B : in std_logic;
		 
		 XO : out std_logic;
		 YO : out std_logic;
		 ZO : out std_logic);
		 end onebitcomparator_beha;
		 
		 architecture Behavioral of onebitcomparator_beha is
		 
		 begin
		 process(A,B)
		 begin
		 if (A>B) then
		 XO <= '1';
		 YO <= '0';
		 ZO <= '0';
		 elsif (A<B) then
		 XO <= '0';
		 YO <= '0';
		 ZO <= '1';
		 else
		 XO <= '0';
		 YO <= '1';
		 ZO <= '0';
		 end if;
		 end process;
		 end Behavioral;