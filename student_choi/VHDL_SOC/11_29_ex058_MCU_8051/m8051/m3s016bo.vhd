--8-bit up counter for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights Reserved.
--v2.000
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s016bo.vhd
--Author        :       RPD
--Library       :       WORK
--Created on    :       8th April 1997
--Purpose       :       8-bit up counter for M8051
--Version       :       2.000
--Mod Date      :       
--Mod History	:
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s015bo.vhd
--                      :
--Calls to              :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s016bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(
            CO:  out std_logic;
            CNT: out std_logic_vector(7 downto 0);
            MODE0,
            LD,
            CI,
            CLEAR,
            COUNT_EN,
            NX1: in std_logic;
            DIN: in std_logic_vector(7 downto 0)
            );
end m3s016bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s016bo_rtl of m3s016bo_e is
--*********************************************************************
--signal definition
--*********************************************************************
signal LCT : std_logic_vector(7 downto 0);
signal C4  : std_logic;
--*********************************************************************
begin
--*********************************************************************
--Process Definitions 
--*********************************************************************
set_count: process(NX1)
-- Loadable synchronous 8-bit counter, with carry look ahead in 4-bit
-- slices.
begin
    if ( NX1'event and NX1 = '1' ) then
        if  CLEAR = '1' then
            LCT <= "00000000";
        elsif COUNT_EN = '1' then
            if LD = '1' then
                LCT <= DIN;
            else

           LCT(0) <= LCT(0) xor CI;
           LCT(1) <= LCT(1) xor ( CI and LCT(0) );
           LCT(2) <= LCT(2) xor ( CI and LCT(0) and LCT(1) );
           LCT(3) <= LCT(3) xor ( CI and LCT(0) and LCT(1) and LCT(2) );

           LCT(4) <= LCT(4) xor C4;
           LCT(5) <= LCT(5) xor ( C4 and LCT(4) );
           LCT(6) <= LCT(6) xor ( C4 and LCT(4) and LCT(5) );
           LCT(7) <= LCT(7) xor ( C4 and LCT(4) and LCT(5) and LCT(6) );

            end if;
        end if;
    end if;
end process set_count;

set_carry: process(LCT, CI, MODE0)
-- Generate counter carry out for five or eight bit modes with
-- combinatorial dependence on the counter carry input.
-- Map local variable to global name for export.
begin
    C4  <= CI and LCT(0) and LCT(1) and LCT(2) and LCT(3);
    CO  <= CI and LCT(0) and LCT(1) and LCT(2) and LCT(3) and LCT(4)
              and ( MODE0 or ( LCT(5) and LCT(6) and LCT(7) ) );
    CNT <= LCT;
end process set_carry;
--*********************************************************************
end m3s016bo_rtl;
--*********************************************************************
