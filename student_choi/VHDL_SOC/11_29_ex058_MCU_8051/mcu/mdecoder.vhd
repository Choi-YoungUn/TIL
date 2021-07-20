-----------------------------------------------------------------------------
-- project  : ISP
-- device   :
-- design   : MCU address decoder
-- author   : nemo
-- file     : mdecoder.vhd
-- version  : 0.0
-- revision : 2006.10.25 : first release
-----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mdecoder is
    port(
      -- system
         rstb     : in std_logic;                     -- reset, active-low

      -- external data access
         mwrn     : in std_logic;                     -- write enable, active-low
         mrdn     : in std_logic;                     -- read enable, active-low
         ma       : in std_logic_vector(15 downto 0); -- read/write address
         mdi      : in std_logic_vector(7 downto 0);  -- write data
         mdo      : out std_logic_vector(7 downto 0); -- read data

      -- system register access
         sr_wrn   : out std_logic;                    -- write enable, active-low
         sr_rdn   : out std_logic;                    -- read enable, active-low
         sr_a     : out std_logic_vector(7 downto 0); -- read/write address
         sr_di    : out std_logic_vector(7 downto 0); -- write data
         sr_do    : in std_logic_vector(7 downto 0);  -- read data

      -- isp register access
         ir_wrn   : out std_logic;                    -- write enable, active-low
         ir_rdn   : out std_logic;                    -- read enable, active-low
         ir_a     : out std_logic_vector(7 downto 0); -- read/write address
         ir_di    : out std_logic_vector(7 downto 0); -- write data
         ir_do    : in std_logic_vector(7 downto 0);  -- read data

      -- peripheral register access
         pr_wrn   : out std_logic;                    -- write enable, active-low
         pr_rdn   : out std_logic;                    -- read enable, active-low
         pr_a     : out std_logic_vector(7 downto 0); -- read/write address
         pr_di    : out std_logic_vector(7 downto 0); -- write data
         pr_do    : in std_logic_vector(7 downto 0)   -- read data
        );
end mdecoder;

architecture rtl of mdecoder is

   constant SYS_ADDR : std_logic_vector(7 downto 0) := "01000000";
   constant ISP_ADDR : std_logic_vector(7 downto 0) := "10000000";
   constant PER_ADDR : std_logic_vector(7 downto 0) := "11000000";

begin

  process(rstb, mwrn, mrdn, ma, mdi, sr_do, ir_do, pr_do)
  begin
    if (rstb = '0') then
      sr_wrn <= '1';
      sr_rdn <= '1';
      sr_a   <= (others => '0');
      sr_di  <= (others => '0');
      ir_wrn <= '1';
      ir_rdn <= '1';
      ir_a   <= (others => '0');
      ir_di  <= (others => '0');
      pr_wrn <= '1';
      pr_rdn <= '1';
      pr_a   <= (others => '0');
      pr_di  <= (others => '0');

      mdo    <= (others => '0');
    elsif (ma(15 downto 8) = SYS_ADDR) then
      sr_wrn <= mwrn;
      sr_rdn <= mrdn;
      sr_a   <= ma(7 downto 0);
      sr_di  <= mdi;
      ir_wrn <= '1';
      ir_rdn <= '1';
      ir_a   <= (others => '0');
      ir_di  <= (others => '0');
      pr_wrn <= '1';
      pr_rdn <= '1';
      pr_a   <= (others => '0');
      pr_di  <= (others => '0');

      mdo    <= sr_do;
    elsif (ma(15 downto 8) = ISP_ADDR) then
      sr_wrn <= '1';
      sr_rdn <= '1';
      sr_a   <= (others => '0');
      sr_di  <= (others => '0');
      ir_wrn <= mwrn;
      ir_rdn <= mrdn;
      ir_a   <= ma(7 downto 0);
      ir_di  <= mdi;
      pr_wrn <= '1';
      pr_rdn <= '1';
      pr_a   <= (others => '0');
      pr_di  <= (others => '0');

      mdo    <= ir_do;
    elsif (ma(15 downto 8) = PER_ADDR) then
      sr_wrn <= '1';
      sr_rdn <= '1';
      sr_a   <= (others => '0');
      sr_di  <= (others => '0');
      ir_wrn <= '1';
      ir_rdn <= '1';
      ir_a   <= (others => '0');
      ir_di  <= (others => '0');
      pr_wrn <= mwrn;
      pr_rdn <= mrdn;
      pr_a   <= ma(7 downto 0);
      pr_di  <= mdi;

      mdo    <= pr_do;
    else
      sr_wrn <= '1';
      sr_rdn <= '1';
      sr_a   <= (others => '0');
      sr_di  <= (others => '0');
      ir_wrn <= '1';
      ir_rdn <= '1';
      ir_a   <= (others => '0');
      ir_di  <= (others => '0');
      pr_wrn <= '1';
      pr_rdn <= '1';
      pr_a   <= (others => '0');
      pr_di  <= (others => '0');

      mdo    <= (others => '0');
    end if;
  end process;

end rtl;
