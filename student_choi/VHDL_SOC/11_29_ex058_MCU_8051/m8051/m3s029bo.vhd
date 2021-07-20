--1 bit up counter(sync clear) for M8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s029bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       13th Dec 1995
--Purpose       :       1 bit up counter(sync clear) for M8051
--Version       :       1.001(Original)
--Mod Date      :       None
--Mod History	:
--
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s028bo.vhd
--                      :
--                      :
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s029bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(CO,
            Q:
            out std_logic;
            CI,
            CLEAR,
            COUNT_EN,
            NX1:
            in std_logic
            );
end m3s029bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s029bo_rtl of m3s029bo_e is
--*********************************************************************
--*********************************************************************
--signal definition
--*********************************************************************
signal LQ,NEXTQ:std_logic;
--*********************************************************************
begin
--*********************************************************************
-- Process Definitions
--*********************************************************************
countr:process(NX1)
begin
    if NX1'event and NX1 ='1' then
        if CLEAR ='1' then
            LQ <= '0';
        elsif COUNT_EN = '1' then
            LQ <= NEXTQ;
        end if;
    end if;
end process countr;
--*********************************************************************
set_nextq:process(LQ,CI,CLEAR)
begin
   NEXTQ <= (LQ or CI) and (not (CI and  LQ)) and not CLEAR;
end process set_nextq;
--*********************************************************************
genout:process(LQ,CI)
begin
   Q <= LQ;
   CO <= CI and  LQ;
end process genout;
--*********************************************************************
end m3s029bo_rtl;
--*********************************************************************


