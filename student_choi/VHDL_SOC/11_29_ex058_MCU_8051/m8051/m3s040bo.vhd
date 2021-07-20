--4 Bit sum generate/propagate for m8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s040bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       12th October 1995
--Purpose       :       4 Bit sum generate/propagate for m8051
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

entity m3s040bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(NGC,
            NPC:
            out std_logic;
            NG,
            P:
            in std_logic_vector(3 downto 0) 
            );       
end m3s040bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s040bo_rtl of m3s040bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,AB,AC,AD:std_logic;
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(P,NG)
begin
   AA <= NG(0) and NG(1) and NG(2) and NG(3);
   AB <= (not P(1)) and NG(1)and NG(2)and NG(3);
   AC <= (not P(2)) and NG(2) and NG(3);
   AD <= (not P(3)) and NG(3);
end process misc1;
--*********************************************************************

sumout:process(AA,AB,AC,AD,P)
begin
   NPC <= not(P(0) and P(1) and P(2) and P(3));
   NGC <= AA or AB or AC or AD;
end process sumout;
--*********************************************************************
end m3s040bo_rtl;
--*********************************************************************
