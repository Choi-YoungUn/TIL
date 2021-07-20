--ALU Controller for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997.  All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s024bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th September 1995
--Purpose       :       ALU control decoder for M8051
--Version       :       1.004
--Mod Date      :       20th March 1997
--Mod History	:       1.004 Name changes
--                      1.003 Sensitivity list revisions. Redundant 
--                            control signals removed.
--                      1.002 INTA removed from decoder for benefit
--                            of synthesis tools.
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s004bo.vhd
--Calls to              :None
--                      :
--                      :
--                      :
---------------------------------------------------
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s024bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ALUC:
            out std_logic_vector(17 downto 0);
            LODEC_4TOF,
            NDIVAB,
            NDJNZD,
            NDJNZR,
            NMULAB,
            DAA,
            NLJMP,
            NLCALL,
            NOP16,
            NCPLB,
            NSETB,
            NSETC,
            NORLCN,
            NORLCB,
            NMOVCB,
            NCLRB,
            NCLRC,
            NANLCN,
            NANLCB,
            JBC,
            NCPLC:
            out std_logic;
            HIDEC:
            in std_logic_vector(15 downto 0);
            LODEC: 
            in std_logic_vector(5 downto 0);--bit 1 not used
            OPC:
            in std_logic_vector(3 downto 1);
            RET,
            RETI:
            in std_logic 
            );       
end m3s024bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s024bo_rtl of m3s024bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AC,AD,AE,AF,AG,AH,AI,AJ,AK,AL,AM,AN,AO,AP,AQ:std_logic;
signal AR,AS,AT,AU,AV,AW,AX,AY,AZ,AAA,AAB,AAC,AAD,AAE,AAF,AAG,AAH:std_logic;
signal BA,BB,BC,BD,BE,CA:std_logic;
--*********************************************************************
--Notes
--ALU Control(ALUC)
--ALUC(0 to 3) are defined as
--       0000- zero accumulator
--       1100- invert accumulator
--       0111- Accumulator add
--       0101- Accumulator EXOR
--       0011- Accumulator Hold
--       0010- Accumulator And
--       1010- Accumulator Subtract
--       0110- Accumulator Load
--ALUC(4) is enable carry
--ALUC(5) is enable borrow
--ALUC(6 and 7)(Rotate control)
--     are defined as 00-No rotate
--                    01-Rotate left
--                    10-Rotate right
--                    11-Swap nibbles
--ALUC(8) is enable half carry load
--ALUC(9 to 12) are defined as
--        0000- Carry = 0
--        1100- Carry = not (LACC(9))
--        0111- Carry = LACC(9) or BBIT
--        0010- Carry = LACC(9) and BBIT
--        1011- Carry = LACC(9) or (not BBIT)
--        0001- Carry = LACC(9) and (not BBIT)
--        0011- Carry = LACC(9)
--        0110- Carry = BBIT
--        1001- Carry = not BBIT
--        1111= Carry = 1
--ALUC(13) is enable carry in 
--ALUC(14) is enable carry out
--ALUC(15) is rotate with carry
--ALUC(16) is Boolean op on carry-(see bits 9 to 12)
--ALUC(17) is NOT enable bit multiplexor
--ALUC(18 and 19) are DV generation 
--
--
--

begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(OPC,HIDEC,LODEC)
begin
   AA <= OPC(2) or OPC(3);
   AB <= HIDEC(1) or HIDEC(9) or HIDEC(11);
   AC <= HIDEC(8) and LODEC(4);
   AD <= HIDEC(15) and LODEC(4);
   AE <= HIDEC(13) and LODEC(5);
   AF <= HIDEC(13) and OPC(3);
   AG <= HIDEC(0)or HIDEC(2)or HIDEC(3);
   AH <= HIDEC(4) or HIDEC(6);
   AI <= OPC(1) or OPC(2) or OPC(3);
   AJ <= HIDEC(10) and LODEC(4);
   AK <= HIDEC(13) and LODEC(4);
   AL <= HIDEC(0) and LODEC(2);
   AM <= HIDEC(1) and LODEC(2);
   AN <= HIDEC(7) or HIDEC(8) or HIDEC(9) or HIDEC(10);
   AO <= HIDEC(14) and LODEC(4);
   AP <= (HIDEC(0) or HIDEC(1)) and LODEC(3);
   AQ <= (HIDEC(2) or HIDEC(3)) and LODEC(3);
   AR <= HIDEC(12) and LODEC(4);
   AS <= HIDEC(2) or HIDEC(3) or HIDEC(9);
   AT <= HIDEC(11) and LODEC(2);
   AU <= HIDEC(13) and LODEC(2);
   AV <= HIDEC(11) and LODEC(3);
   AW <= HIDEC(13) and LODEC(3);
   AX <= HIDEC(10) and LODEC(0);
   AY <= HIDEC(7) and LODEC(2);
   AZ <= HIDEC(10) and LODEC(2);
   AAA <= HIDEC(12) and LODEC(2);
   AAB <= HIDEC(12) and LODEC(3);
   AAC <= HIDEC(11) and LODEC(0);
   AAD <= HIDEC(8) and LODEC(2);
   AAE <= HIDEC(1) and LODEC(0); 
   AAF <= HIDEC(3) or HIDEC(9);
   AAG <= (HIDEC(1) or HIDEC(3)) and LODEC(3);
   AAH <= HIDEC(7)or HIDEC(8)or HIDEC(9)or HIDEC(11)or HIDEC(12)or HIDEC(13);
end process misc1;
--*********************************************************************
misc2:process(AD,AJ,AK,AL,AM,AN,LODEC,RET,RETI)
begin
   BA <= AD or AJ or AK or (LODEC(3) and AN);
   BB <= AL or RET or RETI or AM;
   BC <= (LODEC(3) and AN)or AJ or AK;
end process misc2;
--*********************************************************************
misc3:process(AS,AA,AAH,HIDEC,LODEC)
begin
   BD <= (AA and (AS or HIDEC(11)));
   BE <= AAH and LODEC(2);
end process misc3;
--*********************************************************************
misc4:process(AC,AE,AF,BB)
begin
   CA <= AC or AE or AF or BB;
end process misc4;
--*********************************************************************
aluout1:process(AA,AB,AC,AD,AE,AF,AG,AH,AI,AO,BA,BB,BC,HIDEC)
begin
   ALUC(0) <= (AA and AB) or AC or AD or AE or AF; 
   ALUC(1) <= (AA and AG) or (AH and AI) or BA or BB;
   ALUC(2) <= not(AD or AO or BC or(AG and AA) or (AI and HIDEC(6)));   
end process aluout1;
--*********************************************************************
aluout2:process(AA,AB,AC,AD,AE,AF,AG,AI,AJ,AK,AN,AO,CA,HIDEC,LODEC)
begin
   ALUC(3) <= not(AD or AO or CA or (AA and AB) or (AI and HIDEC(5)));
   ALUC(4) <= AJ or AK or(AA and AG) or (LODEC(3) and AN);
   ALUC(5) <= AC or Af or AE or (AA and AB);
end process aluout2;
--*********************************************************************
aluout3:process(AA,AC,AJ,AP,AQ,AR,AS,AT,AU,AV,AW,AX,AY,AZ)
begin
   ALUC(6) <= AJ or AP or AR;
   ALUC(7) <= AC or AQ or AR;
   ALUC(8) <= AA and AS;
   ALUC(9) <= AT or AU or AV or AW or AX;
   ALUC(10) <= AU or AV or AW or AY or AZ; 
end process aluout3;
--*********************************************************************
aluout4:process(AA,AC,AJ,AN,AT,AV,AZ,BD,AAA,AAB,AAC,AAD,AAE,AAF,LODEC)
begin
   ALUC(11) <= not(AC or AJ or AT or AV or AAA or AAB or AAC or AAE);
   ALUC(12) <= not(AC or AJ or AV or AZ or AAA or AAB or AAD or AAE);
   ALUC(13) <= AA and AAF;
   ALUC(14) <= not(BD or AC or (AN and LODEC(3)));
end process aluout4;
--*********************************************************************
aluout5:process(AC,AJ,AK,AV,AW,AX,AY,AZ,BE,AAB,AAC,AAD,AAE,AAG)
begin
   ALUC(15) <= AJ or AAG;
   ALUC(16) <= not(AC or AJ or AV or AW or AX or AY or AZ or AAB or AAC or AAD);
   ALUC(17) <= not(BE or AAE);
end process aluout5;
--*********************************************************************
miscout1:process(AA,AC,AE,AF,AJ,AK,AL,AM,AN,AT,AU,AW,AX,AY,AZ,LODEC)
begin
   LODEC_4TOF <= AA;
   NDIVAB <= not AC;
   NDJNZD <= not AE;
   NDJNZR <= not AF;
   NMULAB <= not AJ;
   DAA <=  AK;
   NLJMP <= not AL;
   NLCALL <= not AM;
   NOP16 <= not (LODEC(3) and AN);
   NCPLB <= not AT;
   NSETB <= not AU;
   NSETC <= not AW;
   NORLCN <= not AX;
   NORLCB <= not AY;
   NMOVCB <= not AZ;
end process miscout1;
--*********************************************************************
miscout2:process(AAA,AAB,AAC,AAD,AAE,AV)
begin
   NCLRB <= not AAA;
   NCLRC <= not AAB;
   NANLCN <= not AAC;
   NANLCB <= not AAD;
   JBC <= AAE;
   NCPLC <= not AV;
end process miscout2;  
--*********************************************************************
end m3s024bo_rtl;
--*********************************************************************
