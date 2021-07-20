--matrix decode of m8051
--(c)3Soft Limited,1995 All rights reserved
--v1.001
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s022bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       11th September 1995
--Purpose       :       matrix decode of m8051
--Version       :       1.001(Original)
--Mod Date      :       None
--Mod History	:
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s004bo.vhd
--Calls to              :None
--                      :
--                      :
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s022bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(LODEC:
            out std_logic_vector(7 downto 0);
            HIDEC:
            out std_logic_vector(15 downto 0);
            OPC: 
            in std_logic_vector(7 downto 0)
            );       
end m3s022bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s022bo_rtl of m3s022bo_e is
--*********************************************************************

begin
--*********************************************************************
--Process Definitions
--*********************************************************************
matr:process(OPC)
begin
   LODEC(0) <= not(OPC(0) or OPC(1) or OPC(2) or OPC(3));
   LODEC(1) <= not((not OPC(0)) or OPC(1) or OPC(2) or OPC(3));
   LODEC(2) <= not(OPC(0) or (not OPC(1)) or OPC(2) or OPC(3));
   LODEC(3) <= not((not OPC(0)) or (not OPC(1)) or OPC(2) or OPC(3));
   LODEC(4) <= not(OPC(0) or OPC(1) or (not OPC(2)) or OPC(3));
   LODEC(5) <= not((not OPC(0)) or OPC(1) or (not OPC(2)) or OPC(3));
   LODEC(6) <= not(OPC(0) or (not OPC(1)) or (not OPC(2)) or OPC(3));
   LODEC(7) <= not((not OPC(0)) or (not OPC(1)) or (not OPC(2)) or OPC(3));

   HIDEC(0) <= not(OPC(4) or OPC(5) or OPC(6) or OPC(7));
   HIDEC(1) <= not((not OPC(4)) or OPC(5) or OPC(6) or OPC(7));
   HIDEC(2) <= not(OPC(4) or (not OPC(5)) or OPC(6) or OPC(7));
   HIDEC(3) <= not((not OPC(4)) or (not OPC(5)) or OPC(6) or OPC(7));
   HIDEC(4) <= not(OPC(4) or OPC(5) or (not OPC(6)) or OPC(7));
   HIDEC(5) <= not((not OPC(4)) or OPC(5) or (not OPC(6)) or OPC(7));
   HIDEC(6) <= not(OPC(4) or (not OPC(5)) or (not OPC(6)) or OPC(7));
   HIDEC(7) <= not((not OPC(4)) or (not OPC(5)) or (not OPC(6)) or OPC(7));
   HIDEC(8) <= not(OPC(4) or OPC(5) or OPC(6) or (not OPC(7)));
   HIDEC(9) <= not((not OPC(4)) or OPC(5) or OPC(6) or (not OPC(7)));
   HIDEC(10) <= not(OPC(4) or (not OPC(5)) or OPC(6) or (not OPC(7)));
   HIDEC(11) <= not((not OPC(4)) or (not OPC(5)) or OPC(6) or (not OPC(7)));
   HIDEC(12) <= not(OPC(4) or OPC(5) or (not OPC(6)) or (not OPC(7)));
   HIDEC(13) <= not((not OPC(4)) or OPC(5) or (not OPC(6)) or (not OPC(7)));
   HIDEC(14) <= not(OPC(4) or (not OPC(5)) or (not OPC(6)) or (not OPC(7)));
   HIDEC(15) <= not((not OPC(4)) or (not OPC(5)) or (not OPC(6)) or not OPC(7));

end process matr;
--*********************************************************************
end m3s022bo_rtl;
--*********************************************************************
