--M8051 ALU Carry Combiner Element
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights reserved.
--v1.000
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s041bo.vhd
--Author        :       RPD
--Library       :       WORK
--Created on    :       25th March 1997
--Purpose       :       Gate Level ALU Carry Combiner/Look Ahead Element
--Version       :       1.000
--Mod Date      :       
--Mod History	:
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s004bo.vhd
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s041bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(S:    out std_logic_vector(3 downto 0);
            P:    in  std_logic_vector(3 downto 0);
            G:    in  std_logic_vector(2 downto 0);
            C_IN: in  std_logic;
            C_EN: in  std_logic 
            );
end m3s041bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s041bo_rtl of m3s041bo_e is
--*********************************************************************
begin
-- This module combines ALU product/propagate (P) and carry/generate (G)
-- bits to produce carry corrected result (S) of a 4-bit ALU operation
-- (a carry look ahead generator).  It is instantiated separately from
-- the ALU in order to prevent naive synthesis algorithms from producing
-- slow ripple carry implementations of this function.

process(P, G, C_IN, C_EN)
begin
   S(0) <= P(0) xor     C_IN;
   S(1) <= P(1) xor ( ( C_IN and P(0) ) or
                      ( C_EN and G(0) ) );
   S(2) <= P(2) xor ( ( C_IN and P(0) and P(1) ) or
                      ( C_EN and P(1) and G(0) ) or
                      ( C_EN and G(1) ) );
   S(3) <= P(3) xor ( ( C_IN and P(0) and P(1) and P(2) ) or
                      ( C_EN and P(1) and P(2) and G(0) ) or
                      ( C_EN and P(2) and G(1) ) or
                      ( C_EN and G(2) ) );
end process;
--*********************************************************************
end m3s041bo_rtl;
--*********************************************************************
