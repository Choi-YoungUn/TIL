library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity tb_mux_4x1 is  end ;
   
   architecture BEH of tb_mux_4x1 is
   
   component  mux_4x1 is
   port(
   A : in std_logic;
   B : in std_logic;
   C : in std_logic;
   D : in std_logic;
   SEL : in std_logic_vector(1 downto 0);
   
   Y : out std_logic
   );
   end component;
     
     signal siga, sigb, sigc, sigd : std_logic;
     signal sigsel : std_logic_vector(1 downto 0);
     signal sigy : std_logic;
     
   begin
   
   process
   begin
      siga <= '0', '1' after 5 ns;
      wait for 10ns;
      end process;
      
      process
   begin
      sigb <= '0', '1' after 10 ns;
      wait for 20ns;
      end process;
      
      process
   begin
      sigc <= '0', '1' after 20 ns;
      wait for 40ns;
      end process;
      
      process
   begin
      sigd <= '0', '1' after 40 ns;
      wait for 80ns;
   end process;
   
   process
   begin
      sigsel(0) <= '0', '1' after 1000 ns;
      wait for 2000ns;
      end process;
      
      process
   begin
      sigsel(1) <= '0', '1' after 2000 ns;
      wait for 4000ns;
   end process;
   
  u_mux_4x1 : mux_4x1
  port map(
  A => siga,
  B => sigb,
  C => sigc,
  D => sigd,
  SEL => sigsel,
  Y => sigy
  );
  end BEH;
        
   
