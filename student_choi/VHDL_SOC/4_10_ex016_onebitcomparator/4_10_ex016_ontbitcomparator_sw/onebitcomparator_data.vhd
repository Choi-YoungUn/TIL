library ieee;
use ieee.std_logic_1164.all;

entity onebitcomparator_data is
port ( A : in std_logic;
       B : in std_logic;
		 
		 XO : out std_logic;
		 YO : out std_logic;
		 ZO : out std_logic);
		 end onebitcomparator_data;
		 
		 architecture Dataflow of onebitcomparator_data is
		 begin
		 XO <= A and (not B);
		 YO <= A xnor B ;
		 ZO <= (not A) and B ;
		 end Dataflow;
