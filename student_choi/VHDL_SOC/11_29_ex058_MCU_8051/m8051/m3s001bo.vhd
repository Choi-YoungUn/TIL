--Clock Generator and State Machine for M8051
--(c) Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.008
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s001bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       8th September 1995
--Purpose       :       Clock Generator of m8051
--Version       :       1.008
--Mod Date      :       24th March 1997
--Mod History	:       1.008 States 7-12 removed.
--                      1.007 GOCYC3 renamed MULDIV to remove redundancy
--                      1.006 DIV2CK2 revision to continue support for
--                            non-powersaving implementations.
--                      1.005 Idle Mode Power Saving
--			1.004 ECN 823- clash of STD signal naming with
--                                     code coverage tool 
--                      1.003 ECN 838- adjustment to OPC timing
--                      1.002 ECN 817-PCON.0(Idle) timing
--                      1.001(Original)
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--Calls to              :None
--                      :
--                      :
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s001bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(STATD:
            out std_logic_vector(6 downto 1);
            CYC:
            out std_logic_vector(3 downto 1);
            LCYC,
            DIV2CK1,
            DIV2CK2,
            S_EN,
            T_EN,
            STATE12: 
            out std_logic;
            RST,
            GOCYC2,
            MULDIV,
            NX1,
            NX2:
            in std_logic;
            PCON:
            in std_logic_vector(0 downto 0)
            );       
end m3s001bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s001bo_rtl of m3s001bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal LDV2CK1,LDV2CK2,SMA,SMB,SMC,SMD,SME,SMF: std_logic;
signal Q4,Q5,LCYCI: std_logic;
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
--Generates main divided by 2 rate clock
lckdiv:process(NX1,RST)
begin
   if RST = '1' then
      LDV2CK1 <= '0';
      LDV2CK2 <= '0';
   elsif NX1'event and NX1 = '1' then
      LDV2CK1 <= not(LDV2CK1);
      LDV2CK2 <= not(LDV2CK1) or PCON(0); -- remains high in idle
   end if;  
end process lckdiv;
--*********************************************************************
internck:process(LDV2CK1, LDV2CK2)
begin
DIV2CK1 <= LDV2CK1;  
DIV2CK2 <= LDV2CK2;  
end process internck;
--*********************************************************************
st_mhc:process(RST,NX1)
-- A six-position ring counter is the state generator
-- The state counter continues to count during idle mode.
begin
   if RST ='1' then 
      SMA <= '0';
      SMB <= '0';
      SMC <= '0';
      SMD <= '0';
      SME <= '0';
      SMF <= '0';
      S_EN <= '0';
   elsif NX1'event and NX1 ='1' then
      if LDV2CK1='0' then
         SMF <=  not(SMF or SMA or SMB or SMC or SMD);
         SME <= SMD;
         SMD <= SMC;
         SMC <= SMB;
         SMB <= SMA;
         SMA <= SMF;
      end if;
      S_EN <= SME;
   end if;
end process st_mhc;
--*********************************************************************
state6_out:process(RST,NX1)--used for UART, not stopped in idle.
begin
  if RST ='1' then
      STATE12 <= '0';
  elsif NX1'event and NX1='1' then
     if LDV2CK1 = '1' then
         STATE12 <= SMF;
     end if;
   end if;
end process state6_out;
--*********************************************************************
st_out:process(RST,NX2)
-- delayed state outputs, holds at "100000000001" during idle mode.
begin
   if RST ='1' then
      STATD <= "000000";
   elsif NX2'event and NX2='1' then
      if PCON(0) = '0' then
         if LDV2CK2 = '0' then
            STATD(1) <=  SMF;
            STATD(2) <=  SMA;
            STATD(3) <=  SMB;
            STATD(4) <=  SMC;
            STATD(5) <=  SMD;
            STATD(6) <=  SME;
         end if;
      end if;
   end if;
end process st_out;
--*********************************************************************
lcyctimer:process(NX2,RST)
begin
   if RST ='1' then
      LCYC <= '1';
   elsif NX2'event and NX2='1' then
      if (SMA and not LDV2CK2) = '1' then
         LCYC <= LCYCI;
      end if;  
   end if;
end process lcyctimer;
--*********************************************************************
misc_out:process(SMB,SME,Q4,Q5,GOCYC2,MULDIV,LDV2CK1)
begin
   CYC(3) <= Q4 and Q5;
   CYC(2) <= Q4 and (not Q5);
   CYC(1) <= not(Q4 or Q5);
   LCYCI <= (Q4 and Q5 and MULDIV) or (Q4 and not MULDIV) or (not GOCYC2);
   T_EN <= (SMB and not LDV2CK1) or (SME and LDV2CK1);
end process misc_out;
--*********************************************************************
cycle_counter:process(RST,NX2)
-- GOCYC2 from the opcode decoder determines whether an instruction
-- requires a second machine cycle.
-- Only multiply and divide instructions enter cycles 3 and 4.
begin
    if RST ='1' then
        Q4 <= '0';
        Q5 <= '0';
    elsif NX2'event and NX2='1' then
      if (SMF and not LDV2CK2) ='1' then
         if ((Q4 xor Q5)='1') and MULDIV ='1' then
            Q5 <= '1';
         else
            Q5 <= '0';
         end if;
         if ((PCON(0) or Q4 or not GOCYC2) ='1') then
            Q4 <= '0';
         else 
            Q4 <= '1';
         end if ;
      end if;
    end if;
end process cycle_counter;
--*********************************************************************
end m3s001bo_rtl;
--*********************************************************************
