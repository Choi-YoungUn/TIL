--TX shift register for UART of M8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s030bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       14th Dec 1995
--Purpose       :       TX shift register for UART of M8051
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

entity m3s030bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(SOUT,
            QLOW:
            out std_logic;
            NEWDATA,
            CLEAR,
            TSHIFT_EN,
            TSHIFT_IN,
            NX1:
            in std_logic;
            RAMDI:
            in std_logic_vector(7 downto 0)
            );
end m3s030bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s030bo_rtl of m3s030bo_e is
--*********************************************************************
--*********************************************************************
--signal definition
--*********************************************************************
signal DAT:std_logic_vector(7 downto 0);
--*********************************************************************
begin
--*********************************************************************
-- Process Definitions
--*********************************************************************
mrshifter:process(NX1)
begin
    if NX1'event and NX1 ='1' then
        if CLEAR ='1' then
            DAT <= "00000000";
        elsif TSHIFT_EN = '1' then
           if NEWDATA = '1' then
               DAT <= RAMDI;
           else
               DAT(0) <= DAT(1);
               DAT(1) <= DAT(2);
               DAT(2) <= DAT(3);
               DAT(3) <= DAT(4);
               DAT(4) <= DAT(5);
               DAT(5) <= DAT(6);
               DAT(6) <= DAT(7);
               DAT(7) <= TSHIFT_IN;
           end if;
        end if;
    end if;
end process mrshifter;
--*********************************************************************
set_outs:process(DAT)
begin
   SOUT <= DAT(0);
   QLOW <= not(DAT(7) or DAT(6) or DAT(5) or DAT(4) or DAT(3) or DAT(2));
end process set_outs;
--*********************************************************************
end m3s030bo_rtl;
--*********************************************************************


