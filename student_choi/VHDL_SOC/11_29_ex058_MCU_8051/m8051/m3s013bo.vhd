--M8051 Megamacro Program Counter Next Address Multiplexer.
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File          :       m3s013bo.vhd
--Author        :       A. D'Sa
--Library       :       WORK
--Created on    :       4 Jan 1996
--Purpose       :       M8051 Megamacro PC Input Data Multiplexor.
--Version       :       1.004
--Mod Date      :       10th April 1997
--Mod History   :       1.004 Case statements exhaustively defined.
--                      1.003 MUX controls re-written for synthesis.
--                      1.002 Direct path from INTA to program counter
--                            bypassing opcode decoder to avoid
--                            unnecessary multicycle paths in decoder.
--
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s010bo
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s013bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(NEXT_PROGRAM_COUNT:
            out std_logic_vector(15 downto 0);
            VECTOR_ADDR:
            in std_logic_vector(4 downto 1);
            IMMDAT,
            ALUDAT,
            RDAT:
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 5);
            NEXT_REL_PC:
            in std_logic_vector(15 downto 0);
            PCADD:
            in std_logic_vector(2 downto 1);
            NFBL,
            NFBH,
            SEL_11BIT_ADDR,
            INTA:
            in std_logic
            );
end m3s013bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s013bo_rtl of m3s013bo_e is
--*********************************************************************
signal L_YY:std_logic_vector(2 downto 0);
signal LOCALA, ALUDAT_MOD:std_logic_vector(7 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
setlocala:process(PCADD, IMMDAT, RDAT, VECTOR_ADDR, ALUDAT, INTA)
-- Select alternative load source for progam counter low byte.
-- Load interrupt vector during interrupt service ACALL.
begin
   if INTA = '1' then
      -- generate the interrupt vector
      LOCALA(0) <= VECTOR_ADDR(1);
      LOCALA(1) <= VECTOR_ADDR(1);
      LOCALA(2) <= '0';
      LOCALA(5 downto 3) <= VECTOR_ADDR(4 downto 2);
      LOCALA(6) <= '0';
      LOCALA(7) <= '0';
   else
      -- Generate equivalent of mm41B
      case PCADD (2 downto 1) is
          when "00" => LOCALA <= IMMDAT;
          when "01" => LOCALA <= RDAT;
          when "10" => LOCALA <= ALUDAT;
          when "11" => LOCALA <= ALUDAT;
          when others => LOCALA <= "XXXXXXXX";
      end case;
   end if;
end process setlocala;
--*********************************************************************
set_low_addr:process(NFBL, NEXT_REL_PC, LOCALA)
-- Program Counter Low Byte Alternative Source Multiplexer
begin
   case NFBL is
      when  '0' => NEXT_PROGRAM_COUNT(7 downto 0) <= NEXT_REL_PC(7 downto 0);
      when  '1' => NEXT_PROGRAM_COUNT(7 downto 0) <= LOCALA;
      when others => NEXT_PROGRAM_COUNT(7 downto 0) <= "XXXXXXXX";
   end case;
end process set_low_addr;
--*********************************************************************
switch_11bits:process(SEL_11BIT_ADDR, NEXT_REL_PC, OPC)
-- Use opcode to generate upper three bits of an 11-bit address.
-- Used by ACALL and AJMP instructions only.
begin
   case SEL_11BIT_ADDR is
       when '0' => L_YY(2 downto 0) <= NEXT_REL_PC(10 downto 8);
       when '1' => L_YY(2 downto 0) <= OPC(7 downto 5);
       when others => L_YY(2 downto 0) <= "XXX";
   end case;
end process switch_11bits;
--*********************************************************************
set_high_addr:process(NFBH, ALUDAT_MOD, NEXT_REL_PC, L_YY)
-- Program Counter High Byte Alternative Source Multiplexer
begin
   case NFBH is
      when '0' => NEXT_PROGRAM_COUNT(10 downto 8) <= L_YY(2 downto 0);
                  NEXT_PROGRAM_COUNT(15 downto 11) <= NEXT_REL_PC(15 downto 11);
      when '1' => NEXT_PROGRAM_COUNT(15 downto 8) <= ALUDAT_MOD(7 downto 0);
      when others => NEXT_PROGRAM_COUNT(15 downto 8) <= "XXXXXXXX";
   end case;
end process set_high_addr;
--*********************************************************************
set_int_vect_hi: process(ALUDAT, INTA)
-- Force upper address byte to zero during vector to interrupt ACALL.
begin
   case (INTA) is
      when '1' => ALUDAT_MOD(7 downto 0) <= "00000000";
      when '0' => ALUDAT_MOD <= ALUDAT;
      when others => ALUDAT_MOD <= "XXXXXXXX";
   end case;
end process set_int_vect_hi;
--*********************************************************************
end m3s013bo_rtl;
--*********************************************************************
