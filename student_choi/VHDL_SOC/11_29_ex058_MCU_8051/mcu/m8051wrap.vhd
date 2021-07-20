-----------------------------------------------------------------------------
-- project  : ISP
-- device   :
-- design   : M8051 wrapper
-- author   : nemo
-- file     : m8051wrap.vhd
-- version  : 0.0
-- revision : 2006.10.25 : first release
-----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity m8051wrap is
    port(
      -- system
         MRST     : in std_logic;                     -- MCU reset, active-high
         MCLK     : in std_logic;                     -- MCU Clock, rising edge

      -- interrupt
         NINT0    : in std_logic;                     -- External interrupt input 0, active-low
         NINT1    : in std_logic;                     -- External interrupt input 1, active-low

      -- serial-UART
         TXD      : out std_logic;                    -- Serial data to UART
         RXD      : in std_logic;                     -- Serial data from UART

      -- timer
         T0       : in std_logic;                     -- Timer 0 external input
         T1       : in std_logic;                     -- Timer 1 external input

      -- internal program memory
         IPM_NMOE : out std_logic;                    -- output enable, active-low
         IPM_A    : out std_logic_vector(15 downto 0);-- read address
         IPM_DO   : in std_logic_vector(7 downto 0);  -- read data

      -- internal data memory(=SFR)
         IDM_NFOE : out std_logic;                    -- output enable, active-low
         IDM_NFWE : out std_logic;                    -- write enable, active-low
         IDM_A    : out std_logic_vector(7 downto 0); -- read/write address
         IDM_DI   : out std_logic_vector(7 downto 0); -- write data
         IDM_DO   : in std_logic_vector(7 downto 0);  -- read data

      -- external data access
         EDM_NWR  : out std_logic;                    -- write enable, active-low
         EDM_NRD  : out std_logic;                    -- read enable, active-low
         EDM_A    : out std_logic_vector(15 downto 0);-- read/write address
         EDM_DI   : out std_logic_vector(7 downto 0); -- write data
         EDM_DO   : in std_logic_vector(7 downto 0)   -- read data
        );
end m8051wrap;

architecture rtl of m8051wrap is

component m8051
    port(
         NMOE   : out std_logic;
         NMWE   : out std_logic;
         DLM    : out std_logic;
         ALE    : out std_logic;
         NPSEN  : out std_logic;
         NALEN  : out std_logic;
         NFWE   : out std_logic;
         NFOE   : out std_logic;
         NSFRWE : out std_logic;
         NSFROE : out std_logic;
         IDLE   : out std_logic;
         XOFF   : out std_logic;
         OA     : out std_logic_vector(7 downto 0);
         OB     : out std_logic_vector(7 downto 0);
         OC     : out std_logic_vector(7 downto 0);
         OD     : out std_logic_vector(7 downto 0);
         AE     : out std_logic_vector(7 downto 0);
         BE     : out std_logic_vector(7 downto 0);
         CE     : out std_logic_vector(7 downto 0);
         DE     : out std_logic_vector(7 downto 0);
         FA     : out std_logic_vector(7 downto 0);
         FO     : out std_logic_vector(7 downto 0);
         M      : out std_logic_vector(15 downto 0);
         NX1    : in std_logic;
         NX2    : in std_logic;
         RST    : in std_logic;
         NEA    : in std_logic;
         NESFR  : in std_logic;
         ALEI   : in std_logic;
         PSEI   : in std_logic;
         AI     : in std_logic_vector(7 downto 0);
         BI     : in std_logic_vector(7 downto 0);
         CI     : in std_logic_vector(7 downto 0);
         DI     : in std_logic_vector(7 downto 0);
         FI     : in std_logic_vector(7 downto 0);
         MD     : in std_logic_vector(7 downto 0)
        );
end component;

    signal NMOE   : std_logic;
    signal NMWE   : std_logic;
    signal DLM    : std_logic;
    signal ALE    : std_logic;
    signal NPSEN  : std_logic;
    signal NALEN  : std_logic;
    signal NFWE   : std_logic;
    signal NFOE   : std_logic;
    signal NSFRWE : std_logic;
    signal NSFROE : std_logic;
    signal IDLE   : std_logic;
    signal XOFF   : std_logic;
    signal OA     : std_logic_vector(7 downto 0);
    signal OB     : std_logic_vector(7 downto 0);
    signal OC     : std_logic_vector(7 downto 0);
    signal OD     : std_logic_vector(7 downto 0);
    signal AE     : std_logic_vector(7 downto 0);
    signal BE     : std_logic_vector(7 downto 0);
    signal CE     : std_logic_vector(7 downto 0);
    signal DE     : std_logic_vector(7 downto 0);
    signal FA     : std_logic_vector(7 downto 0);
    signal FO     : std_logic_vector(7 downto 0);
    signal M      : std_logic_vector(15 downto 0);
    signal NX1    : std_logic;
    signal NX2    : std_logic;
    signal RST    : std_logic;
    signal NEA    : std_logic;
    signal NESFR  : std_logic;
    signal ALEI   : std_logic;
    signal PSEI   : std_logic;
    signal AI     : std_logic_vector(7 downto 0);
    signal BI     : std_logic_vector(7 downto 0);
    signal CI     : std_logic_vector(7 downto 0);
    signal DI     : std_logic_vector(7 downto 0);
    signal FI     : std_logic_vector(7 downto 0);
    signal MD     : std_logic_vector(7 downto 0);

    signal NWR, NRD : std_logic;

begin

U0 : m8051
  port map(
            NMOE   => NMOE,
            NMWE   => NMWE,
            DLM    => DLM,
            ALE    => ALE,
            NPSEN  => NPSEN,
            NALEN  => NALEN,
            NFWE   => NFWE,
            NFOE   => NFOE,
            NSFRWE => NSFRWE,
            NSFROE => NSFROE,
            IDLE   => IDLE,
            XOFF   => XOFF,
            OA     => OA,
            OB     => OB,
            OC     => OC,
            OD     => OD,
            AE     => AE,
            BE     => BE,
            CE     => CE,
            DE     => DE,
            FA     => FA,
            FO     => FO,
            M      => M,
            NX1    => NX1,
            NX2    => NX2,
            RST    => RST,
            NEA    => NEA,
            NESFR  => NESFR,
            ALEI   => ALEI,
            PSEI   => PSEI,
            AI     => AI,
            BI     => BI,
            CI     => CI,
            DI     => DI,
            FI     => FI,
            MD     => MD
            );

-- internal signal mapping --------------------------------------------------
  RST   <= MRST;
  NX1   <= MCLK;
  NX2   <= (not MCLK) or IDLE;
  NEA   <= '1';
  NESFR <= '1';
  ALEI  <= '0';
  PSEI  <= '0';
  CI    <= "00000000";

  TXD   <= OD(1);
  NWR   <= OD(6);
  NRD   <= OD(7);

  DI    <= "11" & T1 & T0 & NINT1 & NINT0 & '1' & RXD;

-- Internal Program Memory Read ---------------------------------------------
  IPM_NMOE <= NMOE;
  IPM_A    <= M;
  MD       <= IPM_DO;

-- Internal Data Memory Access ----------------------------------------------
  IDM_NFOE <= NFOE;
  IDM_NFWE <= NFWE;
  IDM_A    <= FA;
  IDM_DI   <= FO;
  FI       <= IDM_DO;

-- External Data Memory Access ----------------------------------------------
  EDM_NWR <= NWR;
  EDM_NRD <= NRD;
  EDM_DI  <= OA;
  AI      <= EDM_DO;

  process(NX1, RST)
  begin
    if (RST = '1') then
      EDM_A <= (others => '0');
    elsif (NX1'event and NX1 = '1') then -- 1'clock delay
      if (ALE = '1') then
        EDM_A <= (OC & OA);
--      else
--        EDM_A <= EDM_A;
      end if;
    end if;
  end process;

end rtl;
