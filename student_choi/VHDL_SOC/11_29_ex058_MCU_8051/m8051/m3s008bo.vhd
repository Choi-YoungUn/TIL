-- RAM and Special Function Register Controller for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v2.000
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s008bo.vhd
--Author        :       RPD
--Library       :       WORK
--Created on    :       14th March 1997
--Purpose       :       RAM and SFR controller for M8051
--Version       :       2.000
--Mod Date      :       22nd May 1997 
--Mod History	:       2.000 Re-written for SFR Expansion Capability,
--                            FA and FO outputs registered,
--                            redundancy removed from SFR control.
--                      1.006 Stack read address setup time advanced for
--                            second half of RET instructions.
--                            Direct register bank address generation
--                            simplified.
--                            Bit mode address generator moved.
--                            Sensitivity list revisions.
--			1.005 ECN 878: C_TRUE controls JBC writeback
--                            directly. Direct register bank write backs
--                            now take place at s4p2 in cycle 2.
--                            Indirect addresses stored in separate
--                            register: Ind_Addr.  Data write time
--                            restored to end of S6P2.
--                      1.004 Change to define FA during reset
--                      1.003 Timing correction 
--                      1.002 Calling file name changed to m8051.vhd
--                      1.001 Original
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :m3s009bo.vhd
--                      :m3s039bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s008bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(WEP,
            NFOE,
            NFWE,            
            NSFROE,
            NSFRWE:            
            out std_logic;
            BIT_POSN:
            out std_logic_vector(2 downto 0);
            RAMDI,
            FA,
            RDAT:
            out std_logic_vector(7 downto 0);
            SFRW:
            out std_logic_vector(21 downto 0);
            JBC,
            EITHER_RET,
            C_TRUE,
            NESFR,
            CLEAR,
            LCYC,
            RESINT,
            DIV2CK,
            NX1,
            RST:
            in std_logic;
            ALUDAT,
            IMMDAT,
            SFRDAT,
            SP,
            IROMD,
            FI:
            in std_logic_vector(7 downto 0);
            CYC:
            in std_logic_vector(2 downto 1);
            OPC:
            in std_logic_vector(3 downto 0);
            PSWDAT:
            in std_logic_vector(4 downto 3);
            REGADD:
            in std_logic_vector(10 downto 0);
            STATD:
            in std_logic_vector(6 downto 1);
            STACK_DATA:
            in std_logic_vector(15 downto 0)
            );
end m3s008bo_e;
--*********************************************************************

--Architecture definition
--*********************************************************************
architecture m3s008bo_rtl of m3s008bo_e is
--*********************************************************************
--*********************************************************************
-- Component Definitions
--*********************************************************************
--Register mux
component m3s009bo_e
       port(RAMDI:
            out std_logic_vector(7 downto 0);
            STACK_DATA:
            in std_logic_vector(15 downto 0);
            IMMDAT,
            ALUDAT:
            in std_logic_vector(7 downto 0);
            REGADD:
            in std_logic_vector(1 downto 0);
            CYC:
            in std_logic_vector(2 downto 2);
            STATD:
            in std_logic_vector(5 downto 5);
            RDAT:
            in std_logic_vector(7 downto 4);
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );
end component;
--*********************************************************************
--SFR write strobe decoder sub-module
component m3s039bo_e
       port(
            SFRW:
            out std_logic_vector(21 downto 0);
            WEP:
            out std_logic;
            FA:
            in std_logic_vector(6 downto 0);
            SFR_LOAD,
            SFRWE:
            in std_logic
            );
end component;
--*********************************************************************
--*********************************************************************
--signal definition
--*********************************************************************
signal FA_EN, SFR_LOAD, SEL_SFR_NRAM, JBC_FAILED: std_logic;
signal FOE, FWE, SFROE, SFRWE: std_logic;
signal SEL_DIRADDR, SEL_STACKPTR, SEL_INDADDR, SEL_REGBANK: std_logic;
signal L_FA, L_RDAT, ASYNC_RAMDI: std_logic_vector(7 downto 0);
signal INDIRECT_ADDR, DIRECT_ADDR: std_logic_vector(7 downto 0);
signal REG_BANK_ADDR, BIT_MODE_ADDR: std_logic_vector(7 downto 0);
signal NEXT_FA: std_logic_vector(7 downto 0);
--*********************************************************************
--*********************************************************************
--port mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s009bo_e
  port map(
           RAMDI => ASYNC_RAMDI,
           STACK_DATA => STACK_DATA,
           IMMDAT => IMMDAT,
           ALUDAT => ALUDAT,
           REGADD => REGADD(1 downto 0),
           CYC(2 downto 2) => CYC(2 downto 2),
           STATD(5 downto 5) => STATD(5 downto 5), 
           RDAT => L_RDAT(7 downto 4),
           DIV2CK => DIV2CK,
           NX1 => NX1,
           RST => RST
           );
--*********************************************************************
U2:m3s039bo_e
  port map(
           SFRW => SFRW,
           WEP => WEP,
           FA => L_FA(6 downto 0),
           SFR_LOAD => SFR_LOAD,
           SFRWE => SFRWE
           );
--*********************************************************************

--*********************************************************************
--Process Definitions 
--*********************************************************************
jbc_mask:process( JBC, C_TRUE)
-- prevent register write back in JBC instructions if condition not met
begin
   JBC_FAILED <= JBC and not(C_TRUE);
end process jbc_mask;
--*********************************************************************
gen1:process(CYC, REGADD, STATD, CLEAR, EITHER_RET)
-- Data memory address set at C1S2P1 for indirection register read.
-- Otherwise data memory address generally set at the end of S4P1 only, 
-- except that during a RET instruction the second stack read takes
-- place at C2S1P1.
begin
   FA_EN <= ((CYC(1) and STATD(2)) or
             (CYC(1) and STATD(4)) or
             (CYC(2) and STATD(1) and EITHER_RET) or
             (CYC(2) and STATD(4) and REGADD(2)))
             and not CLEAR;
end process gen1;
--*********************************************************************
mux_direct_addr:process(IMMDAT, IROMD, CYC)
-- When a second direct memory address is required it is first saved in
-- the immediate register during cycle 1 for use in cycle 2 at s4p2.
begin
   if ( CYC(2) ) = '1' then
          DIRECT_ADDR <= IMMDAT;
   else 
          DIRECT_ADDR <= IROMD;
   end if;
end process mux_direct_addr;   
--*********************************************************************
set_addr_mode:process(NX1,RST)
-- Switch file address source from RAM address register to either 
-- previously stored indirect address or register bank address derived
-- combinatorially from the opcode and PSW registers.

begin
   if RST = '1' then
      SEL_DIRADDR <= '1';
      SEL_REGBANK <= '0';
      SEL_INDADDR <= '0';
      SEL_STACKPTR <= '0';
   elsif NX1'event and NX1 ='1' then
      if ( CYC(1) and STATD(1) and DIV2CK ) = '1' then
         -- always start an instruction with a register bank read
         SEL_DIRADDR <= '0';
         SEL_REGBANK <= '1';
         SEL_INDADDR <= '0';
         SEL_STACKPTR <= '0';
      elsif ( STATD(3) and DIV2CK ) = '1' then 
      -- Use REGADD (3&4) to determine addressing mode, unless
      -- addressing mode is required to change (REGADD(2) = 1), in
      -- which case REGADD(5&6) contains the new mode information.
      -- See comments in m3s035bo for details of REGADD encoding.
         if ( CYC(1) or not REGADD(2) ) = '1' then
            SEL_DIRADDR  <= not REGADD(3) and not REGADD(4);
            SEL_REGBANK  <=     REGADD(3) and not REGADD(4);
            SEL_STACKPTR <= not REGADD(3) and     REGADD(4);
            SEL_INDADDR  <=     REGADD(3) and     REGADD(4);
         else
            SEL_DIRADDR  <= not REGADD(5) and not REGADD(6);
            SEL_REGBANK  <=     REGADD(5) and not REGADD(6);
            SEL_STACKPTR <= not REGADD(5) and     REGADD(6);
            SEL_INDADDR  <=     REGADD(5) and     REGADD(6);
         end if;   
      end if;   
   end if;
end process set_addr_mode;
--*********************************************************************
select_next_FA: process(DIRECT_ADDR, REG_BANK_ADDR, INDIRECT_ADDR, SP, 
                        BIT_MODE_ADDR, SEL_REGBANK, SEL_INDADDR,
                        SEL_STACKPTR, SEL_DIRADDR, REGADD) 
-- Main register address multiplexer
-- This 5:1 MUX selects addressing mode and address source.
-- REGADD(10) is decoded from the opcode to select bit addressing mode.
-- SEL_REGBANK, SEL_INDADDR, SEL_STACKPTR and REGADD(10) are mutually
-- exclusive.

begin
   NEXT_FA <= "00000000";
   for I in 0 to 7 loop
      NEXT_FA(I) <=  (SEL_DIRADDR and not REGADD(10) and DIRECT_ADDR(I))
                   or (SEL_DIRADDR and REGADD(10)  and BIT_MODE_ADDR(I))
                   or (SEL_REGBANK and REG_BANK_ADDR(I))
                   or (SEL_STACKPTR and SP(I))
                   or (SEL_INDADDR and INDIRECT_ADDR(I));
   end loop;
end process select_next_FA;
--********************************************************************* 
load_FA: process(NX1, RST)
-- Load register containing address for data memory or SFR accesses.
-- SFRs can be selected as source or destination for direct memory
-- accesses to addresses greater than 80h.
begin
   if RST = '1' then
      L_FA   <= "00000000";
      BIT_POSN <= "000";
      SEL_SFR_NRAM <= '0';
      SFR_LOAD <= '0'; 
   elsif NX1'event and NX1 = '1' then    
      if (FA_EN and DIV2CK) = '1' then
         L_FA   <= NEXT_FA;
         BIT_POSN <= DIRECT_ADDR(2 downto 0);
         SEL_SFR_NRAM <= NEXT_FA(7) and SEL_DIRADDR; 
         SFR_LOAD <=  NEXT_FA(7) and SEL_DIRADDR and
                      not RESINT and REGADD(8);
      end if;
   end if;
end process load_FA;
--********************************************************************* 
file_control:process(NX1,RST)
-- Data memory output enable: this on goes inactive during a data memory
-- write cycle, i.e. from one clock before FWE to one clock after FWE.
-- Data memory writes take place at end of S6P2, i.e. on the falling
-- edge of FWE.
-- always turn off RAM and SFR reads for state 6 of last cycle
begin
   if RST = '1' then
      FOE <= '0';
      FWE <= '0';
      SFRWE <= '0';
      SFROE <= '0';
      RAMDI  <= "00000000";
   elsif NX1'event and NX1 ='1' then
      -- Data memory and SFR read enables
      if ( CYC(1) and STATD(1) ) = '1' then
         -- Always enable data memory at the beginning of a new
         -- instruction in order to load indirect address register.
         FOE <= '1';
         SFROE <= '0';
      elsif (STATD(4) and DIV2CK and not RESINT) = '1' then
         -- Select data memory or SFR as source of register data.
         FOE <= not (NEXT_FA(7) and SEL_DIRADDR); 
         SFROE <= NEXT_FA(7) and SEL_DIRADDR; 
      elsif (STATD(5) and not DIV2CK and not RESINT) = '1' then
         -- Memory is not read after S5 if a register is to be loaded
         -- and is not read at all during CALLs (REGADD(9) = 1).
         FOE   <= not SEL_SFR_NRAM and 
                  not ((LCYC and REGADD(8)) or REGADD(9));
         SFROE <= SEL_SFR_NRAM and
                  not ((LCYC and REGADD(8)) or REGADD(9));
      end if;
      -- Data memory and SFR write strobes
      if STATD(6) = '1' then
         FWE   <=  DIV2CK and not RESINT and
                    ( (LCYC and REGADD(8)) or REGADD(9) )
                    and not SEL_SFR_NRAM and not JBC_FAILED;
         SFRWE <=  DIV2CK and not RESINT and LCYC and REGADD(8)
                    and SEL_SFR_NRAM and not JBC_FAILED;
         RAMDI  <= ASYNC_RAMDI;
      end if;
   end if;
end process file_control; 
--********************************************************************* 
reg_addr_gen: process (OPC, PSWDAT)
-- Generate register bank address from instruction byte.
-- The register bank address is derived from the opcode register
-- directly.  Indirect address generation must take place in the first
-- half of cycle 1 and may only source from R0 or R1. 
begin
   REG_BANK_ADDR(0) <= OPC(0);
   REG_BANK_ADDR(1) <= OPC(1) and OPC(3);         
   REG_BANK_ADDR(2) <= OPC(2) and OPC(3);         
   REG_BANK_ADDR(4 downto 3) <= PSWDAT(4 downto 3);
   REG_BANK_ADDR(7 downto 5) <= "000";
end process reg_addr_gen;
--********************************************************************* 
bit_addr_gen: process(DIRECT_ADDR)
-- generate byte address for bit addressing modes.
begin
   if DIRECT_ADDR(7) ='0' then
      BIT_MODE_ADDR(3 downto 0) <=  DIRECT_ADDR(6 downto 3);
      BIT_MODE_ADDR(4) <= '0';
      BIT_MODE_ADDR(5) <= '1';
      BIT_MODE_ADDR(6) <= '0';
   else
      BIT_MODE_ADDR(2 downto 0) <= "000";
      BIT_MODE_ADDR(6 downto 3) <=  DIRECT_ADDR(6 downto 3);
   end if;
   BIT_MODE_ADDR(7) <=  DIRECT_ADDR(7);
end process bit_addr_gen;
--********************************************************************* 
load_ind_addr: process(NX1, RST)
-- Load indirect address register with data read from register bank. 
-- This always takes place at the start of c1s4p1.
begin
   if RST = '1' then
      INDIRECT_ADDR <= "00000000";
   elsif NX1'event and NX1 ='1' then
      if ( CYC(1) and STATD(3) and not DIV2CK ) ='1' then 
         INDIRECT_ADDR <= FI;
      end if; 
   end if; 
end process load_ind_addr;
--********************************************************************* 
muxrdat:process(SFRDAT, NESFR, FI, SEL_SFR_NRAM)
-- switch register data source from RAM (the default) to SFRs
-- NESFR enables external SFR data to be read in on the FI data bus
begin
   if (SEL_SFR_NRAM and NESFR) ='1' then
      L_RDAT <= SFRDAT;
   else
      L_RDAT <= FI;
   end if;
end process muxrdat;
--********************************************************************* 
localout:process(L_FA, L_RDAT, FOE, FWE, SFROE, SFRWE)
-- Export local signals with their global names
begin
   FA <= L_FA;
   RDAT <= L_RDAT;
   NFOE <= not FOE;
   NFWE <= not FWE;
   NSFROE <= not SFROE;
   NSFRWE <= not SFRWE;
end process localout;
--********************************************************************* 
end m3s008bo_rtl;
--*********************************************************************
