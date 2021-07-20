--Opcode latch sub block for m8051
--(c)3Soft Limited,1996 All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s025bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       03th September 1995
--Purpose       :       Opcode latch sub block for m8051
--Version       :       1.004
--Mod Date      :       2nd September 1996
--Mod History	:       1.004 ECN 838-adjustment to opcode timing
--                      1.003 change for download mode
--                      1.002-Calling file changed to m8051.vhd
--                      1.001(Original)
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--Calls to              :None


--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************
entity m3s025bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(OPC:
            out std_logic_vector(7 downto 0);
            OPLOAD:
            out std_logic;
            IROMD:
            in std_logic_vector(7 downto 0);
            STATD:
            in std_logic_vector(1 downto 1);
            PCON:
            in std_logic_vector(0 downto 0);
            CLEAR,
            RST,
            DIV2CK,
            NX1,
            INTA,
            LCYC,
            DLM:
            in std_logic
            );       
end m3s025bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s025bo_rtl of m3s025bo_e is
--*********************************************************************
--*********************************************************************
--Signal definitions
--*********************************************************************
signal L_OPLOAD:std_logic;
signal LOCALDAT:std_logic_vector(7 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
set_opccon:process(NX1)
begin
   if NX1'event and NX1 ='1' then
        L_OPLOAD <= LCYC and (not CLEAR) and (INTA or not PCON(0)) and not DLM;
   end if;
end process set_opccon;
--*********************************************************************
dat_lat:process(RST,NX1)
begin
    if RST = '1' then 
        OPC <= "00000000";
    elsif NX1'event and NX1 ='1' then
	if (L_OPLOAD  and STATD(1) and DIV2CK) = '1' then
           OPC <= LOCALDAT; 
        end if;

    end if;
end process dat_lat;
--*********************************************************************
dir_con:process(INTA,IROMD)
begin
   if INTA = '0' then
      LOCALDAT <= IROMD;
   else 
      LOCALDAT(0) <= '0';
      LOCALDAT(1) <= '1';
      LOCALDAT(2) <= '0';
      LOCALDAT(3) <= '0';
      LOCALDAT(4) <= '1';
      LOCALDAT(5) <= '0';
      LOCALDAT(6) <= '0';
      LOCALDAT(7) <= '0';
   end if;
end process dir_con;
--*********************************************************************
opcodeout:process(L_OPLOAD)
begin
   OPLOAD <= L_OPLOAD;
end process opcodeout;
--*********************************************************************
end m3s025bo_rtl;
--*********************************************************************

