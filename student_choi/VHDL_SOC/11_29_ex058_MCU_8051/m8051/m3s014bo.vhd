-- Stack Pointer for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights Reserved.
--v1.002
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s014bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       28th November 1995
--Purpose       :       Stack Pointer sub-block of m8051
--Version       :       1.002
--Mod Date      :       11th February 1997
--Mod History	:	1.002 Sensitivity List Revisions.
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s020bo.vhd
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

entity m3s014bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(SP:
            out std_logic_vector(7 downto 0);
            RAMDI:
            in std_logic_vector(7 downto 0);
            SPC:
            in std_logic_vector(1 downto 0);
            SFRW:
            in std_logic_vector(16 downto 16);
            DIV2CK,
            NX1,
            CLEAR,
            ENAB:
            in std_logic 
            );       
end m3s014bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s014bo_rtl of m3s014bo_e is
--*********************************************************************

--*********************************************************************
--Signal definitions
--*********************************************************************
signal L_SP,LOCALA,LOCALB:std_logic_vector(7 downto 0);
signal CD,CU:std_logic_vector(6 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
localout:process(L_SP)
begin
   SP <= L_SP;
end process localout;
--*********************************************************************
muxlocala:process(SFRW, RAMDI, LOCALB)
begin
  case SFRW(16) is
      when '0' => LOCALA <= LOCALB;
      when '1' => LOCALA <= RAMDI;
      when others => LOCALA <= "XXXXXXXX";
  end case;
end process muxlocala;
--*********************************************************************
setsp:process(NX1)
begin
   if (NX1'event and NX1 ='1') then
      if CLEAR ='1' then
           L_SP <= "00000111" ;
      elsif ((ENAB and not DIV2CK)='1') then
           L_SP <= LOCALA;
      end if;
   end if;
end process setsp;
--*********************************************************************
setlocalb:process(SPC,L_SP,CU,CD)
begin
   LOCALB(0) <= (SPC(0) or SPC(1)) XOR L_SP(0);   
   LOCALB(1) <= (CU(0) or CD(0)) XOR L_SP(1);
   LOCALB(2) <= (CU(1) or CD(1)) XOR L_SP(2);
   LOCALB(3) <= (CU(2) or CD(2)) XOR L_SP(3);
   LOCALB(4) <= (CU(3) or CD(3)) XOR L_SP(4);
   LOCALB(5) <= (CU(4) or CD(4)) XOR L_SP(5);
   LOCALB(6) <= (CU(5) or CD(5)) XOR L_SP(6);
   LOCALB(7) <= (CU(6) or CD(6)) XOR L_SP(7);
end process setlocalb;
--*********************************************************************
setcueven:process(SPC, L_SP, CU)
begin 
   CU(0) <= SPC(1) and L_SP(0);
   CU(2) <= CU(1) and L_SP(2);
   CU(4) <= CU(3) and L_SP(4);
   CU(6) <= CU(5) and L_SP(6);
end process setcueven;
--*********************************************************************
setcuodd:process(CU, L_SP)
begin 
   CU(1) <= CU(0) and L_SP(1);
   CU(3) <= CU(2) and L_SP(3);
   CU(5) <= CU(4) and L_SP(5);
end process setcuodd;
--*********************************************************************
setcdeven:process(SPC, L_SP, CD)
begin 
    CD(0) <= SPC(0) and not L_SP(0);
    CD(2) <= CD(1) and not L_SP(2);
    CD(4) <= CD(3) and not L_SP(4);
    CD(6) <= CD(5) and not L_SP(6);
end process setcdeven;
--*********************************************************************
setcdodd:process(CD, L_SP)
begin 
    CD(1) <= CD(0) and not L_SP(1);
    CD(3) <= CD(2) and not L_SP(3);
    CD(5) <= CD(4) and not L_SP(5);
end process setcdodd;
--*********************************************************************
end m3s014bo_rtl;
--*********************************************************************
