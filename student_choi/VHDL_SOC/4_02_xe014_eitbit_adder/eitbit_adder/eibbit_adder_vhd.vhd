library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity eibbit_adder_vhd is

port (
       add_a : in std_logic_vector( 7 downto 0);
		 add_b : in std_logic_vector( 7 downto 0);
		 
		 add_sum : out std_logic_vector( 8 downto 0)
		 );
		 end eibbit_adder_vhd;
		 
		 architecture sample of eibbit_adder_vhd is
		 
		 component half_adder is
		 port(
		    a : in std_logic;
			 b : in std_logic;
			 
			 s : out std_logic;
			 co : out std_logic
		 );
		 end component;

		  component full_adder is
		 port (a : in std_logic;
      b : in std_logic;
		ci : in std_logic;
		
		s : out std_logic;
		co : out std_logic);
		end component;
		
		signal u0_carry : std_logic;
		signal u1_carry : std_logic;
		signal u2_carry : std_logic;
		signal u3_carry : std_logic;
		signal u4_carry : std_logic;
		signal u5_carry : std_logic;
		signal u6_carry : std_logic;
		begin
		
		u0 : half_adder
		port map (
		    a => add_a(0),
			 b => add_b(0),
			 
			 s => add_sum(0),
			 co => u0_carry
		);
		
		u1 : full_adder
		port map (
		    a => add_a(1),
			 b => add_b(1),
			 ci => u0_carry,
			 
			 s => add_sum(1),
			 co => u1_carry
		);
		u2 : full_adder
		port map (
		    a => add_a(2),
			 b => add_b(2),
			 ci => u1_carry,
			 
			 s => add_sum(2),
			 co => u2_carry
		);
		u3 : full_adder
		port map (
		    a => add_a(3),
			 b => add_b(3),
			 ci => u2_carry,
			 
			 s => add_sum(3),
			 co => u3_carry
		);
		u4 : full_adder
		port map (
		    a => add_a(4),
			 b => add_b(4),
			 ci => u3_carry,
			 
			 s => add_sum(4),
			 co => u4_carry
		);
		u5 : full_adder
		port map (
		    a => add_a(5),
			 b => add_b(5),
			 ci => u4_carry,
			 
			 s => add_sum(5),
			 co => u5_carry
		);
		u6 : full_adder
		port map (
		    a => add_a(6),
			 b => add_b(6),
			 ci => u5_carry,
			 
			 s => add_sum(6),
			 co => u6_carry
		);
		u7 : full_adder
		port map (
		    a => add_a(7),
			 b => add_b(7),
			 ci => u6_carry,
			 
			 s => add_sum(7),
			 co => add_sum(8)
		);
		
		end sample;
		