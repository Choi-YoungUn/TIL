-- ALU Temporary Register Number 1 for M8051
--(c) Copyright Mentor Graphics Corporation and Licensees 1997. All Rights Reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s006bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       8th October 1995
--Purpose       :       ALU Temporary Register 1
--Version       :       1.004
--Mod Date      :       11th February 1997
--Mod History	:       1.004 Timing Revision and
--                            unused signals in sensitivity lists.
--                      1.003-OPH and OPL changed to DPH and DPL
--                      1.002-Calling file name changed to m8051.vhd
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

entity m3s006bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(TMPDAT:
            out std_logic_vector(7 downto 0);
            PROGRAM_COUNT:
            in std_logic_vector(15 downto 0);
            RDAT,
            IMMDAT,
            DPH,
            DPL,
            BREG:
            in std_logic_vector(7 downto 0);
            TMPADD:
            in std_logic_vector(3 downto 0);
            CODAT:
            in std_logic_vector(2 downto 0);
            CYC:
            in std_logic_vector(1 downto 1);
            STATD:
            in std_logic_vector(5 downto 2);--4,3 not used
            LOGDI,
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );       
end m3s006bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s006bo_rtl of m3s006bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,TEMP1_EN:std_logic;
signal LDATAA,LDATAB,TEMP1_DATA:std_logic_vector(7 downto 0);
signal MUXVECT1:std_logic_vector(1 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(CYC, LOGDI)
begin
   AA <= CYC(1) or LOGDI;
end process misc1;
--*********************************************************************
gencon:process(AA, STATD, CYC)
begin
   TEMP1_EN <= (AA and STATD(2)) or (CYC(1) and STATD(5)); 
end process gencon;
--*********************************************************************
setmuxvect1:process(TMPADD, STATD)
begin
  MUXVECT1 <= TMPADD(3)&STATD(5);
end process setmuxvect1;
--*********************************************************************
set_abus:process(DPL, DPH, PROGRAM_COUNT, MUXVECT1)
-- select source for 16-bit address arithmetic
begin
  case MUXVECT1 is
      when "00" => LDATAA <= DPL;
      when "01" => LDATAA <= DPH;
      when "10" => LDATAA <= PROGRAM_COUNT(7 downto 0);
      when "11" => LDATAA <= PROGRAM_COUNT(15 downto 8);
      when others => LDATAA <= "XXXXXXXX";
  end case;
end process set_abus;
--*********************************************************************
set_bbus:process(BREG, LDATAA, TMPADD)
begin
  case TMPADD(2) is
      when '0' => LDATAB <= BREG;
      when '1' => LDATAB <= LDATAA;
      when others => LDATAB <= "XXXXXXXX";
  end case;
end process set_bbus;
--*********************************************************************
set_ALU_constant:process(CODAT, IMMDAT, RDAT, LDATAB, TMPADD)
-- generate ALU input constants for increment, decrement and decimal
-- adjust instructions.
begin
  case TMPADD(1 downto 0) is
      when "00" => TEMP1_DATA(1 downto 0) <= CODAT(1 downto 0);
                   TEMP1_DATA(2) <= CODAT(1);
                   TEMP1_DATA(4 downto 3) <= "00";
                   TEMP1_DATA(5) <= CODAT(2);
                   TEMP1_DATA(6) <= CODAT(2);
                   TEMP1_DATA(7) <= '0';
      when "01" => TEMP1_DATA <= IMMDAT;
      when "10" => TEMP1_DATA <= RDAT;
      when "11" => TEMP1_DATA <= LDATAB;
      when others => TEMP1_DATA <= "XXXXXXXX";
  end case;
end process set_ALU_constant;
--*********************************************************************
tmpout:process(NX1,RST)
begin
    if RST ='1' then
       TMPDAT <= "00000000";
    elsif NX1'event and NX1 ='1' then
       if (TEMP1_EN and not DIV2CK) ='1' then
           TMPDAT <= TEMP1_DATA;
       end if;
    end if;
end process tmpout;
--*********************************************************************
end m3s006bo_rtl;
--*********************************************************************
