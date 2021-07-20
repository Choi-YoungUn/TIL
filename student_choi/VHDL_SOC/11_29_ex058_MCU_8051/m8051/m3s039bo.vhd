--m3s039bo Special Function Register Write Strobe Generator
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s039bo.vhd
--Author        :       A. D'Sa
--Library       :       WORK
--Created on    :       20th Oct 1995
--Purpose       :       Write strobe and load mux  control generator
--Version       :       1.004
--Mod Date      :       14th March 1997
--Mod History	:	1.004 Redundancy removed.
--                      1.003 SFR expansion capability added, address
--                            decoder re-written for legibility.
--                      1.002 Synthesis Fixes
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s008bo.vhd
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************
entity m3s039bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(
            SFRW:
            out std_logic_vector(21 downto 0);
            WEP:
            out std_logic;
            FA:
            in std_logic_vector(6 downto 0);
            SFR_LOAD,
            SFRWE:
            in std_logic
            );
end m3s039bo_e;


--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s039bo_rtl of m3s039bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal A000, A001, A010, A011, A100, A101, A111: std_logic;
signal AH0000, AH0001, AH0010, AH0011, AH0100, AH0110: std_logic;
signal AH1010, AH1100, AH1110, AH1111, AH01X1: std_logic;
--*********************************************************************
begin
--Notes
--
-- SFRW BUS LINES
--  0 WRITE PORT0
--  1 WRITE PORT1
--  2 WRITE PORT2
--  3 WRITE PORT3
--  4 WRITE TCON
--  5 WRITE TMOD
--  6 WRITE TLO
--  7 WRITE TL1
--  8 WRITE TH0
--  9 WRITE TH1
-- 10 WRITE SCON
-- 11 WRITE SBUF
-- 12 WRITE IE
-- 13 WRITE IP
-- 14 WRITE DPL
-- 15 WRITE DPH
-- 16 WRITE SP
-- 17 WRITE PSW
-- 18 WRITE PCON
-- 19 WRITE MSIZ
-- 20 WRITE B
-- 21 WRITE ACCUMULATOR

--*********************************************************************
--Process Definitions
--*********************************************************************

addr_decode1:process(FA)
-- Generate intermediate SFR address decoding
begin

-- Decodes for the lower three data memory address bits.
A000 <= not FA(2) and not FA(1) and not FA(0);
A001 <= not FA(2) and not FA(1) and     FA(0);
A010 <= not FA(2) and     FA(1) and not FA(0);
A011 <= not FA(2) and     FA(1) and     FA(0);
A100 <=     FA(2) and not FA(1) and not FA(0);
A101 <=     FA(2) and not FA(1) and     FA(0);
A111 <=     FA(2) and     FA(1) and     FA(0);

-- Decodes for data memory address bits 3 to 6.
AH0000 <= not FA(6) and not FA(5) and not FA(4) and not FA(3);
AH0001 <= not FA(6) and not FA(5) and not FA(4) and     FA(3);
AH0010 <= not FA(6) and not FA(5) and     FA(4) and not FA(3);
AH0011 <= not FA(6) and not FA(5) and     FA(4) and     FA(3);
AH0100 <= not FA(6) and     FA(5) and not FA(4) and not FA(3);
AH0110 <= not FA(6) and     FA(5) and     FA(4) and not FA(3);
AH1010 <=     FA(6) and not FA(5) and     FA(4) and not FA(3);
AH1100 <=     FA(6) and     FA(5) and not FA(4) and not FA(3);
AH1110 <=     FA(6) and     FA(5) and     FA(4) and not FA(3);
AH1111 <=     FA(6) and     FA(5) and     FA(4) and     FA(3);

AH01X1 <= not FA(6) and     FA(5) and                   FA(3);

end process addr_decode1;
--*********************************************************************
sfrout:process(A000, A001, A010, A011, A100, A101, A111, AH0000, AH0001,
               AH0010, AH0011, AH0100, AH0110, AH1010, AH1100, AH1110,
               AH1111, AH01X1, FA, SFRWE, SFR_LOAD)
-- Use address decodes to drive SFR write enables at end of S6P2.

begin
SFRW(21) <= SFRWE and AH1100 and A000;
SFRW(20) <= SFRWE and AH1110 and A000;
SFRW(19) <= SFRWE and AH1111 and A111;
SFRW(18) <= SFRWE and AH0000 and A111;
SFRW(17) <= SFRWE and AH1010 and A000;
SFRW(16) <= SFRWE and AH0000 and A001;
SFRW(15) <= SFRWE and AH0000 and A011;
SFRW(14) <= SFRWE and AH0000 and A010;
SFRW(13) <= SFRWE and AH01X1 and A000 and FA(4);
SFRW(12) <= SFRWE and AH01X1 and A000 and not FA(4);
SFRW(11) <= SFRWE and AH0011 and A001;
SFRW(10) <= SFRWE and AH0011 and A000;

SFRW(9) <=  SFRWE and AH0001 and A101; 
SFRW(8) <=  SFRWE and AH0001 and A100;
SFRW(7) <=  SFRWE and AH0001 and A011; 
SFRW(6) <=  SFRWE and AH0001 and A010;
SFRW(5) <=  SFRWE and AH0001 and A001;
SFRW(4) <=  SFRWE and AH0001 and A000;

SFRW(3) <=  SFRWE and AH0110 and A000;
SFRW(2) <=  SFRWE and AH0100 and A000;
SFRW(1) <=  SFRWE and AH0010 and A000;
SFRW(0) <=  SFRWE and AH0000 and A000;

-- Disable interrupts during write to IE or IP
  
WEP  <=  SFR_LOAD and AH01X1 and A000;

end process sfrout;
end m3s039bo_rtl;
--*********************************************************************
