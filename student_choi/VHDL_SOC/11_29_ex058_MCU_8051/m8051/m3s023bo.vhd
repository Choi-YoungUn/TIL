-- SFR Output Multiplexer sub-block of M8051
--(c) Copyright Mentor graphics Corporation and Licensors 1997. All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s023bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       23th October 1995
--Purpose       :       SFR multiplexor sub-block of m8051
--Version       :       1.004
--Mod Date      :       29th January 1997
--Mod History	:       1.004 Unused addresses no longer inject 'X's
--                      1.003 OPL and OPH changed to DPL and DPH 
--                      1.002-Calling file changed to m8051.vhd
--                      1.001(Original)
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
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

entity m3s023bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(SFRDAT:
            out std_logic_vector(7 downto 0);
            FA:
            in std_logic_vector(6 downto 0);
            PORTA,
            PORTB,
            PORTC,
            PORTD,
            SP,
            DPL,
            DPH,
            PCON,
            TCON,
            TMOD,
            TLA,
            TLB,
            THA,
            THB,
            SCON,
            SBUF,
            IE,
            IP,
            PSWDAT,
            ACCDAT,
            BREG,
            MSIZ:
            in std_logic_vector(7 downto 0)
            );       
end m3s023bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s023bo_rtl of m3s023bo_e is
--*********************************************************************

--*********************************************************************
--*********************************************************************
-- Sub-Multiplexer Outputs
signal SUB_SERIAL, SUB_TIMER, SUB_MISC: std_logic_vector(7 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
set_sub_muxes: process(FA, PORTA, SP, DPL, DPH, PCON,
                           TCON, TMOD, TLA, TLB, THA, THB)
begin
   case FA(2 downto 0) is
      when "000" =>  SUB_TIMER <= TCON;
                     SUB_MISC  <= PORTA;
      when "001" =>  SUB_TIMER <= TMOD;
                     SUB_MISC  <= SP;
      when "010" =>  SUB_TIMER <= TLA;
                     SUB_MISC  <= DPL;
      when "011" =>  SUB_TIMER <= TLB;
                     SUB_MISC  <= DPH;
      when "100" =>  SUB_TIMER <= THA;
                     SUB_MISC  <= PORTA;
      when "101" =>  SUB_TIMER <= THB;
                     SUB_MISC  <= SP;
      when "110" =>  SUB_TIMER <= THA;
                     SUB_MISC  <= DPL;
      when "111" =>  SUB_TIMER <= THB;
                     SUB_MISC  <= PCON;
      when others => SUB_TIMER <= "XXXXXXXX";
                     SUB_MISC  <= "XXXXXXXX";
   end case;
end process set_sub_muxes;
--*********************************************************************
set_sub_serial: process(FA, SCON, SBUF)
begin
   case FA(0) is
      when '0' =>    SUB_SERIAL <= SCON;
      when '1' =>    SUB_SERIAL <= SBUF;
      when others => SUB_SERIAL <= "XXXXXXXX";
   end case;
end process set_sub_serial;
--*********************************************************************
set_sfr:process(FA, SUB_MISC, SUB_TIMER, PORTB, SUB_SERIAL, PORTC,
                IE, PORTD, IP, PSWDAT, ACCDAT, BREG, MSIZ)
begin
  case FA(6 downto 3) is
      when "0000" => SFRDAT <= SUB_MISC;
      when "0001" => SFRDAT <= SUB_TIMER;
      when "0010" => SFRDAT <= PORTB;
      when "0011" => SFRDAT <= SUB_SERIAL;
      when "0100" => SFRDAT <= PORTC;
      when "0101" => SFRDAT <= IE;
      when "0110" => SFRDAT <= PORTD;
      when "0111" => SFRDAT <= IP;
      when "1000" => SFRDAT <= PSWDAT;
      when "1001" => SFRDAT <= PSWDAT;
      when "1010" => SFRDAT <= PSWDAT;
      when "1011" => SFRDAT <= PSWDAT;
      when "1100" => SFRDAT <= ACCDAT;
      when "1101" => SFRDAT <= ACCDAT;
      when "1110" => SFRDAT <= BREG;
      when "1111" => SFRDAT <= MSIZ;
      when others => SFRDAT <= "XXXXXXXX";
  end case;
end process set_sfr;
--*********************************************************************
end m3s023bo_rtl;
--*********************************************************************
