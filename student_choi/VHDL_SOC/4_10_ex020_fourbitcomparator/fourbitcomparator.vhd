library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity fourbitcomparator is
port (Ai : in std_logic_vector(3 downto 0);
      Bi : in std_logic_vector(3 downto 0);
		Xif : in std_logic;
		Yif : in std_logic;
		Zif : in std_logic;
		
		Xof : out std_logic;
		Yof : out std_logic;
		Zof : out std_logic);
		end fourbitcomparator;
		
		architecture sample of fourbitcomparator is
		
		component onebitfullcomparator_vh is
	 port ( A : in std_logic;
       B : in std_logic;
		 Xi : in std_logic;
		 Yi : in std_logic;
		 Zi : in std_logic;
		 
		 Xo : out std_logic;
		 Yo : out std_logic;
		 Zo : out std_logic);
		 end component;
		
		signal x3 : std_logic;
		signal y3 : std_logic;
		signal z3 : std_logic;
		
		signal x2 : std_logic;
		signal y2 : std_logic;
		signal z2 : std_logic;
		
		signal x1 : std_logic;
		signal y1 : std_logic;
		signal z1 : std_logic;
		
		begin
		u3 : onebitfullcomparator_vh
		port map( A => Ai(3),
	             B => Bi(3),
					Xi => Xif,
				   Yi => Yif,
				   Zi => Zif,	
					
					Xo => x3,
					Yo => y3,
					Zo => z3
		       );
		 u2 : onebitfullcomparator_vh
		port map( A => Ai(2),
	             B => Bi(2),
					Xi => x3,
				   Yi => y3,
				   Zi => z3,	
					
					Xo => x2,
					Yo => y2,
					Zo => z2
		       );
		 u1 : onebitfullcomparator_vh
		port map( A => Ai(1),
	             B => Bi(1),
					Xi => x2,
				   Yi => y2,
				   Zi => z2,	
					
					Xo => x1,
					Yo => y1,
					Zo => z1
		       );
		 u0 : onebitfullcomparator_vh
		port map( A => Ai(0),
	             B => Bi(0),
					Xi => x1,
				   Yi => y1,
				   Zi => z1,	
					
					Xo => Xof,
					Yo => Yof,
					Zo => Zof
		       );
		
		end sample;