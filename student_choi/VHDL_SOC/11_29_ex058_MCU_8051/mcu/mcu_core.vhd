-----------------------------------------------------------------------------
-- project  : ISP
-- device   :
-- design   : MCU core
-- author   : nemo
-- file     : mcu_core.vhd
-- version  : 0.0
-- revision : 2006.10.25 : first release
-----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mcu_core is
    port(
      -- system
         rstb     : in std_logic;                     -- reset, active-low
         mclk     : in std_logic;                     -- Clock, rising edge

      -- interrupt
         nint0    : in std_logic;                     -- External interrupt input 0, active-low
         nint1    : in std_logic;                     -- External interrupt input 1, active-low

      -- serial-UART
         txd      : out std_logic;                    -- Serial data to UART
         rxd      : in std_logic;                     -- Serial data from UART

      -- timer
         t0       : in std_logic;                     -- Timer 0 external input
         t1       : in std_logic;                     -- Timer 1 external input

      -- external data access
         mwrn     : out std_logic;                    -- write enable, active-low
         mrdn     : out std_logic;                    -- read enable, active-low
         ma       : out std_logic_vector(7 downto 0);-- read/write address
         mdi      : out std_logic_vector(7 downto 0); -- write data
         mdo      : in std_logic_vector(7 downto 0)   -- read data
        );
end mcu_core;

architecture rtl of mcu_core is

component m8051wrap
    port(
         MRST     : in std_logic;
         MCLK     : in std_logic;

         NINT0    : in std_logic;
         NINT1    : in std_logic;

         TXD      : out std_logic;
         RXD      : in std_logic;

         T0       : in std_logic;
         T1       : in std_logic;

         IPM_NMOE : out std_logic;
         IPM_A    : out std_logic_vector(15 downto 0);
         IPM_DO   : in std_logic_vector(7 downto 0);

         IDM_NFOE : out std_logic;
         IDM_NFWE : out std_logic;
         IDM_A    : out std_logic_vector(7 downto 0);
         IDM_DI   : out std_logic_vector(7 downto 0);
         IDM_DO   : in std_logic_vector(7 downto 0);

         EDM_NWR  : out std_logic;
         EDM_NRD  : out std_logic;
         EDM_A    : out std_logic_vector(15 downto 0);
         EDM_DI   : out std_logic_vector(7 downto 0);
         EDM_DO   : in std_logic_vector(7 downto 0)
        );
end component;

--component spram256x8
--    port(
--	 Clock    : in  std_logic; 
--	 ClockEn  : in  std_logic; 
--	 Reset    : in  std_logic; 
--	 WE       : in  std_logic; 
--	 Address  : in  std_logic_vector(7 downto 0); 
--	 Data     : in  std_logic_vector(7 downto 0); 
--	 Q        : out  std_logic_vector(7 downto 0));
--end component;

--component spram2kx8
--    port(
--         Address    : in  std_logic_vector(10 downto 0); 
--         OutClock   : in  std_logic; 
--         OutClockEn : in  std_logic; 
--         Reset      : in  std_logic; 
--         Q          : out  std_logic_vector(7 downto 0));
--end component;

--component spram8kx8  -- 8k
--    port (
--	  Address    : in  std_logic_vector(12 downto 0); 
--	  OutClock   : in  std_logic; 
--	  OutClockEn : in  std_logic; 
--	  Reset      : in  std_logic; 
--	  Q          : out  std_logic_vector(7 downto 0));
--end component;
component R0M8192x8
	port (
		address	: in	std_logic_vector(12 downto 0);
		clock	: in	std_logic;
		q	: out	std_logic_vector( 7 downto 0)
	);
end component;

component RAM256x8
	port (
		address	: in	std_logic_vector( 7 downto 0);
		clock	: in	std_logic;
		data	: in	std_logic_vector( 7 downto 0);
		wren	: in	std_logic;
		q	: out	std_logic_vector( 7 downto 0)
	);
end component;

    signal mrst     : std_logic;

    signal ipm_nmoe : std_logic;
    signal ipm_a    : std_logic_vector(15 downto 0);
    signal ipm_do   : std_logic_vector(7 downto 0);

    signal idm_nfoe : std_logic;
    signal idm_nfwe : std_logic;
    signal idm_a    : std_logic_vector(7 downto 0);
    signal idm_di   : std_logic_vector(7 downto 0);
    signal idm_do   : std_logic_vector(7 downto 0);

    -- appletree
    signal not_idm_nfwe 	: std_logic;
	
	signal mad : std_logic_vector(15 downto 0);
	
begin

  mrst <= not rstb;
	ma <= mad(7 downto 0);
-----------------------------------------------------------------------------
U0 : m8051wrap
    port map (
         MRST     => mrst,
         MCLK     => mclk,

         NINT0    => nint0,
         NINT1    => nint1,

         TXD      => txd,
         RXD      => rxd,

         T0       => t0,
         T1       => t1,

         IPM_NMOE => ipm_nmoe,
         IPM_A    => ipm_a,
         IPM_DO   => ipm_do,

         IDM_NFOE => idm_nfoe,
         IDM_NFWE => idm_nfwe,
         IDM_A    => idm_a,
         IDM_DI   => idm_di,
         IDM_DO   => idm_do,

         EDM_NWR  => mwrn,
         EDM_NRD  => mrdn,
         EDM_A    => mad,
         EDM_DI   => mdi,
         EDM_DO   => mdo
        );

---- internal program memory --------------------------------------------------
--spram2kx8 prg_ram(
--                   .addr(ipm_a[`PROM_WIDTH-1:0]),
--                   .clk (mclk       ),
--                   .din (8'b0       ),
--                   .dout(ipm_do     ),
--                   .en  (1'b1       ),
--                   .we  (1'b0       )
--                  );

---- internal data memory -----------------------------------------------------
--spram256x8 sfr_ram(
--                   .addr(idm_a    ),
--                   .clk (mclk     ),
--                   .din (idm_di   ),
--                   .dout(idm_do   ),
--                   .en  (1'b1     ),
--                   .we  (~idm_nfwe)
--                  );

-----------------------------------------------------------------------------

--prg_ram : spram8kx8
--port map(
--	  Address    => ipm_a(12 downto 0), --: in  std_logic_vector(11 downto 0); 
--	  OutClock   => mclk,               --: in  std_logic; 
--	  OutClockEn => '1',                --: in  std_logic; 
--	  Reset      => mrst,               --: in  std_logic; 
--	  Q          => ipm_do              --: out  std_logic_vector(7 downto 0));
--	);
--
--not_idm_nfwe <= not idm_nfwe;
--
--sfr_ram : spram256x8
--port map(
--	 Clock      => mclk,              --: in  std_logic; 
--	 ClockEn    => '1',               --: in  std_logic; 
--	 Reset      => mrst,              --: in  std_logic; 
--	 WE         => not_idm_nfwe,      --: in  std_logic; 
--	 Address    => idm_a,             --: in  std_logic_vector(7 downto 0); 
--	 Data       => idm_di,            --: in  std_logic_vector(7 downto 0); 
--	 Q          => idm_do             --: out  std_logic_vector(7 downto 0)
--	);

not_idm_nfwe <= not idm_nfwe;

prg_ram : R0M8192x8
port map (
		address	=> ipm_a(12 downto 0),
		clock	=> mclk,
		q	=> ipm_do
	);

sfr_ram : RAM256x8
port map (
		address	=> idm_a,
		clock	=> mclk,
		data	=> idm_di,
		wren	=> not_idm_nfwe,
		q	=> idm_do
	);
	
end rtl;
