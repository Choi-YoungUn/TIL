library ieee;
use ieee.std_logic_1164.all;

package my_demux1x8 is
    procedure demux1x8_proce (signal I : in std_logic;
	 signal S : in std_logic_vector(2 downto 0);
	 signal O : out std_logic_vector(7 downto 0));
	 end my_demux1x8;
	 
	 package body my_demux1x8 is
	 
	 procedure demux1x8_proce (signal I : in std_logic;
	 signal S : in std_logic_vector(2 downto 0);
	 signal O : out std_logic_vector(7 downto 0)) is
	 
	 begin 
	 case S is
	 when "111"  => O <=      I & "0000000";
	 when "110"  => O <= '0' & I & "000000";
	 when "101"  => O <= "00" & I & "00000";
	 when "100"  => O <= "000" & I & "0000";
	 when "011"  => O <= "0000" & I & "000";
	 when "010"  => O <= "00000" & I & "00";
	 when "001"  => O <= "000000" & I & '0';
	 when others => O <= "0000000" & I     ;
	 end case;
	 end demux1x8_proce;
	 
	 end my_demux1x8;
	 