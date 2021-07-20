--RX shift register for UART of M8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s031bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       14th Dec 1995
--Purpose       :       RX shift register for UART of M8051
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

entity m3s031bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(
            FRM:
            out std_logic_vector(7 downto 0);
            D0,
            LORCV,
            RSHIFT_EN,
            RSHIFT_IN,
            NX1:
            in std_logic
            );
end m3s031bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s031bo_rtl of m3s031bo_e is
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
        if RSHIFT_EN = '1' then 
            if LORCV ='1' then
                DAT(6 downto 0) <= "1111111";
                DAT(7) <= D0;
            else
               DAT(0) <= DAT(1);
               DAT(1) <= DAT(2);
               DAT(2) <= DAT(3);
               DAT(3) <= DAT(4);
               DAT(4) <= DAT(5);
               DAT(5) <= DAT(6);
               DAT(6) <= DAT(7);
               DAT(7) <= RSHIFT_IN;
            end if;
        end if;
    end if;
end process mrshifter;
--*********************************************************************
set_outs:process(DAT)
begin
   FRM <= DAT;
end process set_outs;
--*********************************************************************
end m3s031bo_rtl;
--*********************************************************************


