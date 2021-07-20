--Program Counter control decoder for m8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.005
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s034bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th September 1995
--Purpose       :       Program Counter control of m8051
--Version       :       1.005
--Mod Date      :       11th February 1997
--Mod History	:       1.005 Sensitivity List Revisions.
--                      1.004 Comments Corrected.
--                      1.003 ECN 878: CTRU and INTA removed from
--                            decoder logic.
--			1.002 Changes to match dummy address cycles
--                      1.001 Original 
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
entity m3s034bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(PCADD:
            out std_logic_vector(12 downto 1);
            HIDEC:
            in std_logic_vector(15 downto 0);--bits 4 to 6 and 12,13 not used
            LODEC:
            in std_logic_vector(5 downto 0);
            OPC:
            in std_logic_vector(7 downto 3);--bits 7 and 3 only used
            NLCALL,
            BRET,
            PCL0,
            DJNZ,
            CJNE,
            NIDP,
            INDOP,
            LOGDI,
            NDJR,
            NDJD:
            in std_logic 
            );       
end m3s034bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s034bo_rtl of m3s034bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AD,AE,AG,AH,AI,AK,AL:std_logic;
signal BB,BC,BD,BE:std_logic;
--*********************************************************************
--Notes
--Program Counter Controls (PCADD) are defined by the following tables:

--          12345 12 Function
--          ----- -- --------------------------------------
--          000XX  X Load PC low from immediate
--          100XX  X Load PC low from register
--          010XX  X Load PC low interupt vector 
--          110XX  X Load PC low from ALU
--          XX100  0 Load PC from incrementer
--          XX101  0 Load PC for conditional jump relative
--          XX100  1 Load PC for short jump relative (SJMP) 
--          XX00X  X Load PC high from opcode
--          XXX1X  X Load PC high from ALU
--
--          678      Function
--          ---      --------------------------------------
--          0XX      program counter fetch from memory
--          1XX      data pointer fetch from memory
--          XX1      load data pointer from reg
--          X00      load data pointer from imm
--          X10      load data pointer from ALU
--         
--          9 10 11  Function
--          - -- --  --------------------------------------
--          1  X  X  Fetch a second program byte
--          X  1  0  Fetch a third program byte at beginning of cycle 2
--          X  0  1  Fetch a third program byte at middle of cycle 2
--
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(HIDEC,LODEC,BRET,PCL0,OPC,INDOP,CJNE,LOGDI)
begin
   AA <= HIDEC(7) and LODEC(3);
   AB <= BRET or PCL0;
   AD <= LODEC(0) and (not OPC(7)) and (not HIDEC(0));
   AE <= HIDEC(9) and LODEC(0);
   AG <= LODEC(1) or LODEC(5);
   AH <= HIDEC(14) or HIDEC(15) or HIDEC(2) or HIDEC(3) or HIDEC(7) or HIDEC(8) or HIDEC(9);
   AI <= INDOP or OPC(3);
   AK <= (HIDEC(9) or HIDEC(11)) and OPC(7) and LODEC(4);
   AL <= (not(HIDEC(0) or HIDEC(1) or OPC(7))) and LODEC(4);
end process misc1;
--*********************************************************************
misc2:process(AA,AI,AH,DJNZ,CJNE,BRET,LODEC,HIDEC)
begin
--   BB <= AA or INTA or BRET;
   BB <= AA or BRET;
   BC <= LODEC(0) and (HIDEC(1) or HIDEC(2) or HIDEC(3) or HIDEC(9));
   BD <= AI and (HIDEC(7) or HIDEC(11));
   BE <= (not AH) and LODEC(2); 
end process misc2;
--*********************************************************************
pcout1:process(AA, AB, AD, BB, HIDEC, LODEC, PCL0, BRET, DJNZ, CJNE )
begin
   PCADD(1) <= AA or BRET; 
--   PCADD(2) <= AA or INTA;
   PCADD(2) <= AA;
   PCADD(3) <= not (BB or LODEC(1) or PCL0);
--   PCADD(4) <= AA or AB or INTA;
   PCADD(4) <= AA or AB;
   PCADD(5) <= AD or DJNZ or CJNE;       -- conditional branches
   PCADD(12) <= HIDEC(8) and LODEC(0);   -- short jump (branch always)
end process pcout1;
--*********************************************************************
pcout2:process(AE,AG,AK,AL,BC,BD,BE,HIDEC,LODEC,NIDP,LOGDI,NDJR,NDJD,CJNE,PCL0,OPC,INDOP,NLCALL)
begin
   PCADD(6) <= (HIDEC(8) or HIDEC(9)) and LODEC(3);
   PCADD(7) <= not NIDP;
   PCADD(8) <= NIDP and (not AE);
   PCADD(9) <= BC or AG or BE or BD or LOGDI  or AK or AL;

   if HIDEC(8 downto 1) = "00000000" then
        PCADD(10) <= CJNE or (not NLCALL) or (not NDJD) or not NDJR;
   else
        PCADD(10) <= LODEC(0) or CJNE or (not NDJD) or not NDJR or not NLCALL;
   end if;
   
   PCADD(11) <= (OPC(3) and (HIDEC(8) or HIDEC(10))) or 
                (LODEC(0) and (HIDEC(9) or HIDEC(10) or HIDEC(11) or HIDEC(12) or HIDEC(13))) or
                (LODEC(2) and (HIDEC(7) or HIDEC(8) or HIDEC(9))) or
                (LODEC(5) and (HIDEC(7) or HIDEC(8))) or
                (INDOP and (HIDEC(8) or HIDEC(10))) or LOGDI;
end process pcout2;
--*********************************************************************
end m3s034bo_rtl;
--*********************************************************************



