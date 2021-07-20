--Register File Control Decoder for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.003
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s035bo.vhd
--Author        :       A. D'Sa
--Library       :       WORK
--Created on    :       4 Jan 1996
--Purpose       :       M8051 Register File Control Decoder
--Version       :       1.003
--Mod Date      :       12th March 1997
--Mod History	:	1.003 Comments added for REGADD(5-10)
--                      1.002 ECN 878: CTRU removed from decoder
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s004bo.vhd
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s035bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(REGADD:
            out std_logic_vector(10 downto 0);
            NCALL,
            NPOP,
            NPUSH:
            out std_logic;
            HIDA:
            in std_logic_vector(3 downto 0);
            LODEC:
            in std_logic_vector(2 downto 0);
            OPC:
            in std_logic_vector(4 downto 3);
            HIDB:
            in std_logic_vector(8 downto 7);
            HIDC:
            in std_logic_vector(13 downto 10);
            HI15,
            L5TF,
            NLCA,
            BRET,
            INDOP,
            INDXR,
            INDXW,
            NLDA,
            LOGDI,
            NMBC,
            JBC,
            NBEN,
            NSWA,
            NMCB:
            in std_logic
            );
end m3s035bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s035bo_rtl of m3s035bo_e is
--*********************************************************************
signal AA,AB,AC,AD,AE,AF,AG,AH,AI,AJ,AK,AL,AM,AO,AP:std_logic;
signal BB,BC,BD,BE,BF,BG:std_logic;
signal NSPA:std_logic;
--*********************************************************************
begin
--Notes
--Register File Mux Control (REGADD) defined as
--
--REGADD (0 to 4)
--
--      0 1 2 3 4 Function
--      --------------------
--      0 0 X X X Load Register from ALU
--      1 0 X X X Load Register from IMM
--      0 1 X X X Load Register for Nibble Swap
--      1 1 X X X Load Register from PC
--      X X 0 X X Register Address Unchanged
--      X X 1 X X Reg Address Control: cycle1 - bits 3&4, in cyc2 - 5&6.
--      X X X 0 0 Register Address Direct
--      X X X 1 0 Register Address Register Bank
--      X X X 0 1 Register Address Stack Pointer
--      X X X 1 1 Register Address Indirect
--
-- REGADD (4 to 10)
--
--      5 6 7 8 9 10   Function
--      ---------------------------------------------------------------
--      0 0 X X X X    Second Register Address Direct
--      1 0 X X X X    Second Register Address Register Bank
--      0 1 X X X X    Second Register Address Stack Pointer
--      1 1 X X X X    Second Register Address Indirect
--      X X 0 X X X    Not Register Indirect Address Enable
--      X X 1 X X X    Register Indirect Address Enable
--      X X X 0 X X    No Register Load 
--      X X X 1 X X    Register Load 
--      X X X X 0 X    No Second Register Load
--      X X X X 1 X    Second Register Load (used by CALL instructions)
--      X X X X X 0    Not Register Bit Addressing Mode
--      X X X X X 1    Register Bit Addressing Mode
--
--*********************************************************************
misc1:process(HIDA,HIDB,HIDC,HI15,JBC,L5TF,LODEC,INDOP,INDXR,INDXW,OPC,NLCA)
begin
-- Generate intermediate signal prior to producing regadd(0,1,2,3,4)
AA <= HIDB(7) and L5TF;
AB <= (LODEC(1) and OPC(4)) or (not NLCA);
AC <= (HIDC(12) or HIDC(13)) and LODEC(0);
AD <= L5TF and HIDB(8);
AE <= (INDOP or OPC(3)) and HIDC(10);
AF <= OPC(3) and (not HIDC(10));
AG <= HIDC(13) and LODEC(0);
AH <= HIDC(10) or not INDOP;
AI <= not (INDXR or INDXW);
--generate intermediate signals prior to producing regadd(5,6,7,8,9,10)
AJ <= HIDC(10) and OPC(3);
AK <= HIDC(12) and LODEC(0);
AL <= INDOP and HIDC(10);
AM <= HIDA(0) or HIDA(1) or HIDB(7) or HIDB(8) or HIDC(10) or HIDC(12) or HIDC(13) or HI15;
AO <= HIDC(11) or HIDC(12) or HIDC(13);
AP <= HIDA(2) or HIDA(3) or HIDC(10) or HIDC(11);
end process misc1;
--*********************************************************************
misc2:process(AB,AH,AI,AK,AJ,AL,AM,AO,AP,NSPA,LODEC,L5TF)
begin
BB <= AH and AI;
BC <= AJ or AL;
BD <= AK or AL or (not NSPA);
BE <= AM and L5TF;
BF <= AO and LODEC(2);
BG <= AP and LODEC(0);
end process misc2;
--*********************************************************************
regout1:process(AA,AB,AC,AD,AE,AF,AG,BB,NSWA,NSPA)
begin
REGADD(0) <= AA or AB ;
REGADD(1) <= (not NSWA) or AB; 
REGADD(2) <= AC or AD or AE or (not NSPA);
REGADD(3) <= AF or (not BB);
REGADD(4) <= AG or (not NSPA) or (not BB);
end process regout1;
--*********************************************************************
regout2:process(AB,AC,BC,BD,BE,BF,BG,INDXR,INDXW,INDOP,NLDA,LOGDI,NMBC,NMCB,NBEN, JBC)
begin
REGADD(5) <= BC;
REGADD(6) <= BD;
REGADD(7) <= INDXR or INDXW or INDOP;
REGADD(8) <= BE or AB  or AC or (not NLDA) or LOGDI or (not NMBC) or JBC or BF;
REGADD(9) <= AB;
REGADD(10) <= BG or (not NBEN) or (not NMCB);
end process regout2;
--*********************************************************************
miscout:process(AB,AC,AG,AK,BRET)
begin
NCALL <= not AB;
NPOP <= not AG;
NSPA <= not (BRET or AB);
NPUSH <= not AK;
end process miscout;
--*********************************************************************
end m3s035bo_rtl;
--*********************************************************************
