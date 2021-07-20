--4 Bit sum sub-block for m8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s027bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       12th October 1995
--Purpose       :       4 Bit sum sub-block for m8051
--Version       :       1.001(Original)
--Mod Date      :       None
--Mod History	:
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s011bo.vhd
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

entity m3s027bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(SUM:
            out std_logic_vector(3 downto 0);
            NG,
            P:
            in std_logic_vector(3 downto 0);
            NCI:
            in std_logic 
            );       
end m3s027bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s027bo_rtl of m3s027bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AC,AD,AE,AF,AG,AH,AI,AJ:std_logic;
signal BA,BB,BC:std_logic;
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(P,NG,NCI)
begin
   AA <= P(3) and NG(3);
   AB <= (not P(1)) and NG(2);
   AC <= (not P(0)) and NG(2) and NG(1);
   AD <= NCI and NG(2) and NG(1) and NG(0);
   AE <= P(2) and NG(2);
   AF <= (not P(0)) and NG(1);
   AG <= NCI and NG(1) and NG(0);
   AH <= P(1) and NG(1);
   AI <= NCI and NG(0);
   AJ <= P(0) and NG(0);
end process misc1;
--*********************************************************************
misc2:process(P,AB,AC,AD,AF,AG,AI)
begin
   BA <= (not P(2)) or AB or AC or AD;
   BB <= (not P(1)) or AF or AG;
   BC <= (not P(0)) or AI;
end process misc2;
--*********************************************************************
sumout:process(AA,AE,AH,AJ,BA,BB,BC,NCI)
begin
   SUM(0) <= (not AJ) xor NCI;
   SUM(1) <= (not AH) xor BC;
   SUM(2) <= (not AE) xor BB;
   SUM(3) <= (not AA) xor BA;
end process sumout;
--*********************************************************************
end m3s027bo_rtl;
--*********************************************************************
