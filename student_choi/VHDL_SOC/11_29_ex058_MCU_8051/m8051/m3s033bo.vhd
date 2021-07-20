--Accumulator, B Register and ALU Temporary Register 2 Control Decoder
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights Reserved.
--v1.003
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s033bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th September 1995
--Purpose       :       accumulator mux control of m8051
--Version       :       1.003
--Mod Date      :       20th March 1997
--Mod History	:       1.003 Name changes
--                      1.002 ECN 878: temp register 2 given extra load
--                            times.
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
entity m3s033bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ACCADD:
            out std_logic_vector(9 downto 0);
            NMOVPC,
            NINCDP,
            NSWAPN,
            NMOVBC,
            LOGDI:
            out std_logic;
            HIDEC:
            in std_logic_vector(14 downto 0);
            LODEC: 
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 3);-- bits 4,5 not used
            LODEC_4TOF,
            NOP16,
            MULDIV,
            INDXR,
            INDOP,
            NDIV,
            NDJD,
            NDJR,
            NBEN,
            CJNE,
            NMUL,
            NMCB:
            in std_logic 
            );       
end m3s033bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s033bo_rtl of m3s033bo_e is
--*********************************************************************
--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AC,AD,AE,AF,AG,AH,AI,AJ,AK,AL,AM,AN,AP,AQ:std_logic;
signal BA,BB,BC,BE,BF,CA,CB:std_logic;
--*********************************************************************
--Notes
--Accumulator address (ACCADD) defined as follows:
--
--      3210   Function
--      ----   ------------------------------------
--      00XX   Load Accumultor from ALU
--      10XX   Load Accumulator immediate
--      01XX   Load Accumulator from register
--      110X   Load Accumulator for multiplier
--      111X   Load Accumulator for division
--      XX00   Load Temp Register 2 from accumulator
--      XX01   Load Temp Register 2 from Register
--      XX11   Load Temp Register 2 for Mult/Div

--ACCADD(4) enables nibble exchange
--ACCADD(5) generates constants for 16 bit operations
--ACCADD(6) generates increment for INC DPTR
--ACCADD(7) enables accumulator load
--ACCADD(8) enables load accumulator for exchange
--ACCADD(9) enables extra instructions to load temp register 2 at c2s2p2
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(HIDEC,LODEC)
begin
   AA <= HIDEC(7) and LODEC(4);
   AB <= HIDEC(14) and LODEC(0);
   AC <= HIDEC(8) and LODEC(3);
   AD <= HIDEC(9) and LODEC(3);
   AE <= HIDEC(12) or HIDEC(13) or HIDEC(14);
   AF <= (HIDEC(12) or HIDEC(14)) and LODEC(5);
   AG <= HIDEC(2) or HIDEC(3) or HIDEC(10) or HIDEC(11) or HIDEC(12) or
         HIDEC(13);
   AH <= HIDEC(0) or HIDEC(1) or HIDEC(8) or HIDEC(10);
   AI <= HIDEC(4) or HIDEC(5) or HIDEC(6);
   AJ <= (LODEC(6) or LODEC(7)) and HIDEC(13);
   AK <= HIDEC(10) and LODEC(3);
   AL <= not HIDEC(11) and LODEC(4);
   AM <= HIDEC(14) and not LODEC(1);
   AN <= HIDEC(2) or HIDEC(3) or HIDEC(4) or HIDEC(5); 
   AP <= HIDEC(9) and LODEC(2);
   AQ <= LODEC(4) or LODEC(5);
end process misc1;
--*********************************************************************
misc2:process(HIDEC,OPC,AH,NDJD,NDJR,NBEN,NMCB,LODEC_4TOF,LODEC)
begin
   BA <= (HIDEC(12) or HIDEC(14)) and OPC(3);
   BB <= NDJD and NDJR and NBEN and NMCB;
   BC <= not AH or not LODEC_4TOF or LODEC(4);
end process misc2;
--*********************************************************************
misc3:process(AN,AQ,CJNE,HIDEC)
begin
   BE <= AQ or not CJNE;
   BF <= HIDEC(6) or HIDEC(9) or HIDEC(14) or AN;
end process misc3;
--*********************************************************************
misc4:process(AC,AD,LODEC_4TOF,AN,BB,BC,BF,AG,AI,LODEC)
begin
   CA <= BB and BC and (not(AG and LODEC(0)))and (not(AI and LODEC(3)));
   CB <= AC or AD or (LODEC_4TOF and  BF);
end process misc4;
--*********************************************************************
accout1:process(NDIV,NMUL,MULDIV,INDXR,INDOP,AA,AB,AC,AD,AE,AF,BA,BE,CA)
begin
   ACCADD(0) <= MULDIV or INDXR or AA or AB or AC or AD; 
   ACCADD(1) <= MULDIV or AF or BA or (AE and INDOP);
   ACCADD(2) <= not NDIV;
   ACCADD(3) <= not(NDIV and BE and CA and NMUL);
   ACCADD(9) <= NDIV and not(BE and CA and NMUL);
end process accout1;
--*********************************************************************
accout2:process(AJ,NOP16,AK,AL,AM,CB,LODEC,HIDEC,OPC,LODEC_4TOF)
begin
   ACCADD(4) <= AJ;
   ACCADD(5) <= not NOP16;
   ACCADD(6) <= AK;
   ACCADD(7) <= AL or AM or CB or (LODEC(3) and not OPC(6) and not OPC(7) );
   ACCADD(8) <= AJ or (HIDEC(12) and LODEC_4TOF);
end process accout2;
--*********************************************************************
miscout:process(AC,AI,AJ,AK,AP,LODEC)
begin
   NMOVPC <= not AC; 
   LOGDI  <= AI and LODEC(3);
   NSWAPN <= not AJ;
   NINCDP <= not AK;
   NMOVBC <= not AP; 
end process miscout;  
--*********************************************************************
end m3s033bo_rtl;
--*********************************************************************
