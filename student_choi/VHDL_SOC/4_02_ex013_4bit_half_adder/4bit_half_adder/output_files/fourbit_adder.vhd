library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity fourbit_adder is
port (
        add_a : in std_logic_vector( 3 downto 0);
		  add_b : in std_logic_vector( 3 downto 0);
		  
		  add_sum : out std_logic_vector( 4 downto 0)
);
end fourbit_adder;

architecture sample of fourbit_adder is

component half_adder is
port ( 
        a : in std_logic;
		  b : in std_logic;
		  
		  s : out std_logic;
		  co : out std_logic
		  );
		  end component;
		  
		  component full_adder is
		  port (
		  fa : in std_logic;
		  fb : in std_logic;
		  fcin : in std_logic;
		  
		  fs : out std_logic;
		  fco : out std_logic
		  );
		  end component;
		  
		  signal u0_carry :std_logic;
		  signal u1_carry :std_logic;
		  signal u2_carry :std_logic;
		  begin
		  u0 : half_adder
		  port map (
		       a => add_a(0),
				 b => add_b(0),
				 
				 s => add_sum(0),
				 co =>u0_carry
				 );
				 
				 u1 : full_adder
				 port map (
				  fa => add_a(1),
				  fb => add_b(1),
				  fcin => u0_carry,
				  
				  fs => add_sum(1),
				  fco => u1_carry
				 );
				 
				 u2 : full_adder
				 port map (
				  fa => add_a(1),
				  fb => add_b(1),
				  fcin => u1_carry,
				  
				  fs => add_sum(1),
				  fco => u2_carry
				 );
				 
				 u3 : full_adder
				 port map (
				  fa => add_a(3),
				  fb => add_b(3),
				  fcin => u2_carry,
				  
				  fs => add_sum(3),
				  fco => add_sum(4)
				 );
				 
				 end sample;
		  