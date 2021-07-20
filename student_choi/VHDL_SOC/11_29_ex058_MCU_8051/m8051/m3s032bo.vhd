-- ALU Temporary Register Number 1 Control Decoder for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.003
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s032bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th September 1995
--Purpose       :       Temporary latch control of m8051
--Version       :       1.003
--Mod Date      :       20th March 1997
--Mod History	:	1.003 Name changes
--                      1.002: Name Changes and BRET decoder moved to
--                             module m3s004bo. Sensitivity list 
--                             revisions.
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s004bo.vhd
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

entity m3s032bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(TMPADD:
            out std_logic_vector(3 downto 0);
            PCLONG,
            LO5TOF,
            NLOGDA:
            out std_logic;
            HIDEC:
            in std_logic_vector(11 downto 2);--bits 7,8 and 10 not used
            LODEC: 
            in std_logic_vector(5 downto 2);-- bit 3 not used
            LODEC_4TOF,
            ND16,
            MULDIV,
            NMPC,
            NLCA,
            NLJM,
            EITHER_RET,
            LOGDI:
            in std_logic 
            );       
end m3s032bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s032bo_rtl of m3s032bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AC,AD,AE,AF,AH:std_logic;
signal BA,BB,BC,BD,BE:std_logic;
--*********************************************************************
--Notes
--Temporary register number 1 control bus (TMPADD) defined as
--TMPADD(0 to 3)
--             0123 Function
--             ==== ====================================================
--             00XX Load Temp1 with a constant generated from the opcode
--             10XX Load Temp1 from Immediate data register
--             01XX Load Temp1 from register memory
--             110X Load Temp1 from B Register
--             1110 Load Temp1 from Data Pointer (DPTR)
--             1111 Load Temp1 from Program Counter
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(HIDEC,LODEC,NLCA,NLJM,LODEC_4TOF,MULDIV,ND16)
begin
   AA <= NLCA and NLJM;
   AB <= not LODEC_4TOF or LODEC(5);
   AC <= HIDEC(4) or HIDEC(5) or HIDEC(6);
   AD <= HIDEC(2) or HIDEC(3) or HIDEC(9);
   AE <= LODEC(5) and HIDEC(11);
   AF <= LODEC(4) or not LODEC_4TOF;
   AH <= ND16 and not MULDIV;
end process misc1;
--*********************************************************************
misc2:process(AB,AC,AD,AE,AF,LODEC,HIDEC)
begin
   BA <= LODEC(4) and AC;
   BB <= LODEC(4) and AD;
   BC <= LODEC(2) and AC;
   BD <= (AC or AD or AE) and not AF;
   BE <= not(AB or not HIDEC(11));
end process misc2;
--*********************************************************************
tmpout1:process(AA,AH,BA,BB,BC,BD,BE,LOGDI,MULDIV,NMPC,EITHER_RET)
begin
   TMPADD(0) <= LOGDI or not AA or not AH or BA or BB or BE; 
   TMPADD(1) <= BC or BD or EITHER_RET or not AH;
   TMPADD(2) <= not MULDIV;
   TMPADD(3) <= not NMPC;
end process tmpout1;
--*********************************************************************
miscout:process(AA, AF, BC)
-- Map local signal names to global names
begin
   PCLONG <= not AA;
   LO5TOF <= not AF;
   NLOGDA <= not BC; 
end process miscout;  
--*********************************************************************
end m3s032bo_rtl;
--*********************************************************************
