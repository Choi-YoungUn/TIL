library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity fourbit_addsub is

port (
       addsub_a : in std_logic_vector( 3 downto 0);
		 addsub_b : in std_logic_vector( 3 downto 0);
		 Msign : in std_logic;
		 addsub_num : out std_logic_vector( 4 downto 0)
		 );
		 end fourbit_addsub;
		 
		 architecture sample of fourbit_addsub is
		 
		  component full_adder is
		 port (a : in std_logic;
      b : in std_logic;
		ci : in std_logic;
		
		s : out std_logic;
		co : out std_logic);
		end component;
		
		component XOR_Gate is
		 port(A,B: in std_logic;
	   C : out std_logic);
		end component;
		
		signal u0_carry : std_logic;
		signal u1_carry : std_logic;
		signal u2_carry : std_logic;
		signal b0_xor : std_logic;
		signal b1_xor : std_logic;
		signal b2_xor : std_logic;
		signal b3_xor : std_logic;
		begin
		
		b0 : XOR_Gate
		port map (
		   A => Msign,
			B => addsub_b(0),
			
			c => b0_xor
		);

		u0 : full_adder
		port map (
		    a => addsub_a(0),
			 b => b0_xor,
			 ci => Msign,
			 
			 s => addsub_num(0),
			 co => u0_carry
		);
		
		b1 : XOR_Gate
		port map (
		   A => Msign,
			B => addsub_b(1),
			
			c => b1_xor
		);
		
		u1 : full_adder
		port map (
		    a => addsub_a(1),
			 b => b1_xor,
			 ci => u0_carry,
			 
			 s => addsub_num(1),
			 co => u1_carry
		);
		
		b2 : XOR_Gate
		port map (
		   A => Msign,
			B => addsub_b(2),
			
			c => b2_xor
		);
		
		u2 : full_adder
		port map (
		    a => addsub_a(2),
			 b => b2_xor,
			 ci => u1_carry,
			 
			 s => addsub_num(2),
			 co => u2_carry
		);
		b3 : XOR_Gate
		port map (
		   A => Msign,
			B => addsub_b(3),
			
			c => b3_xor
		);
		
		u3 : full_adder
		port map (
		    a => addsub_a(3),
			 b => b3_xor,
			 ci => u2_carry,
			 
			 s => addsub_num(3),
			 co => addsub_num(4)
		);
		
		end sample;