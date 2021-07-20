-- Register Write Data Multiplexer sub-block of M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.005
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s009bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th October 1995
--Purpose       :       Register multiplexor sub-block of m8051
--Version       :       1.005
--Mod Date      :       20th March 1997 
--Mod History	:       1.005 STATDs 7-12 abandoned.
--                      1.004 XCHD register timing retarded to S5P2
--                      1.003 Delay data change until beginning of S1P2.
--                      1.002 Timing change to LDATAB(nibble swap latch)
--                      1.001 Original
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s008bo.vhd
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

entity m3s009bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(RAMDI:
            out std_logic_vector(7 downto 0);
            STACK_DATA:
            in std_logic_vector(15 downto 0);
            IMMDAT,
            ALUDAT:
            in std_logic_vector(7 downto 0);
            REGADD:
            in std_logic_vector(1 downto 0);
            CYC:
            in std_logic_vector(2 downto 2);
            STATD:
            in std_logic_vector(5 downto 5);
            RDAT:
            in std_logic_vector(7 downto 4);
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );       
end m3s009bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s009bo_rtl of m3s009bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal LDATAA:std_logic_vector(7 downto 0);
signal REG_HI_NIBBLE:std_logic_vector(7 downto 4);
signal STACK_MUX: std_logic;
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
stack_mux_selector:process(NX1, RST)
-- Delay write data switch over to beginning of S1P2 to avoid race
-- with NFWE at end of S6P2.
begin
    if RST ='1' then
       STACK_MUX <= '0';
    elsif NX1'event and NX1 ='1' then
       if DIV2CK = '1' then
           STACK_MUX <= CYC(2);
       end if;
    end if;
end process stack_mux_selector;
--*********************************************************************
set_abus:process(STACK_DATA, STACK_MUX)
-- Select program address byte for writing to stack during CALL and PUSH
-- instructions.
begin
  case STACK_MUX is
      when '0' => LDATAA <= STACK_DATA(7 downto 0);
      when '1' => LDATAA <= STACK_DATA(15 downto 8);
      when others => LDATAA <= "XXXXXXXX";
  end case;
end process set_abus;
--*********************************************************************
set_outbus:process(REGADD, ALUDAT, IMMDAT, REG_HI_NIBBLE, LDATAA )
begin
  case REGADD(1 downto 0) is
      when "00" => RAMDI <= ALUDAT;
      when "01" => RAMDI <= IMMDAT;
      when "10" => RAMDI(3 downto 0) <= ALUDAT(3 downto 0);
                   RAMDI(7 downto 4) <= REG_HI_NIBBLE; 
      when "11" => RAMDI <= LDATAA;
      when others => RAMDI <="XXXXXXXX";
  end case;
end process set_outbus;
--*********************************************************************
upper_nibble_temp:process(NX1,RST)
-- Temporary Data Memory Upper Nibble register
-- Used by Exchange Digit instruction (XCHD) to store dat memory nibble
-- Loads at the end of S5P2 (same as for temporary registers 1 and 2).
begin
    if RST ='1' then
       REG_HI_NIBBLE <= "0000";
    elsif NX1'event and NX1 ='1' then
       if (STATD(5) and not DIV2CK) ='1' then
           REG_HI_NIBBLE <= RDAT(7 downto 4);
       end if;
    end if;
end process upper_nibble_temp;
--*********************************************************************
end m3s009bo_rtl;
--*********************************************************************
