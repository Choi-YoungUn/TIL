--Conditional jump test subblock for m8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.007
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s007bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       8th October 1995
--Purpose       :       conditional jump test subblock for M8051
--Version       :       1.007
--Mod Date      :       24th March 1997
--Mod History	:       1.007 STATDs 7-12 removed
--                      1.006 Sensivity List Revisions
--                      1.005 C_TRUE clocked at c2s4p1
--                      1.004-CTRU only clocked at end of CYC1
--                      1.003-changed CA inverted, CTRU delayed
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

entity m3s007bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(C_TRUE:
            out std_logic;
            ALUDAT:
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 4);
            PSWDAT:
            in std_logic_vector(7 downto 7);
            CYC:
            in std_logic_vector(2 downto 2);
            STATD:
            in std_logic_vector(3 downto 3);
            BBIT,
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );       
end m3s007bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s007bo_rtl of m3s007bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal AA,CA,TMPCTRU:std_logic; 
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
accumulator_zero:process(ALUDAT)
-- test for zero in the accumulator via ALU bus
begin
   AA <= ALUDAT(0) or ALUDAT(1) or ALUDAT(2) or ALUDAT(3) or ALUDAT(4)
         or ALUDAT(5) or ALUDAT(6) or ALUDAT(7);
end process accumulator_zero;
--*********************************************************************
misc3:process(OPC,PSWDAT,BBIT,AA)
begin
  case OPC(6 downto 4) is
      when "000" => CA <= '1';
      when "001" => CA <= BBIT;
      when "010" => CA <= BBIT;
      when "011" => CA <= not BBIT;
      when "100" => CA <= PSWDAT(7);
      when "101" => CA <= not PSWDAT(7);
      when "110" => CA <= not AA;
      when "111" => CA <= AA;
      when others => CA <= 'X';
  end case;
end process misc3;
--*********************************************************************
misc4:process(OPC, AA, CA)
begin
  case OPC(7) is
      when '0' => TMPCTRU <= CA;
      when '1' => TMPCTRU <= AA;
      when others => TMPCTRU<= 'X';
  end case;
end process misc4;
--*********************************************************************
ctruout:process(NX1,RST)
-- Updates condition at the beginning of c2s4p1.  This output is used by
-- module m3s010bo at c2s5p1 and module m3s008 at c2s5p2 for jbc writes.
begin
    if RST ='1' then
       C_TRUE <= '0';
    elsif NX1'event and NX1 ='1' then
       if (CYC(2) and STATD(3) and not DIV2CK) ='1' then
           C_TRUE <= TMPCTRU;
       end if;
     end if;
end process ctruout;
--*********************************************************************
end m3s007bo_rtl;
--*********************************************************************










