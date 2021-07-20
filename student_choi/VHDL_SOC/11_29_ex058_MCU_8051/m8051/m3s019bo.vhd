--Interrupt Controller for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors. All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s019bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       13th Dec 1995
--Purpose       :       Interrupt control and priority regs etc for M8051
--Version       :       1.004
--Mod Date      :       11th February 1997
--Mod History	:       1.004 Name changes and sensitivity list
--                            revisions.
--                      1.003 Idle Mode Power Saving
--			1.002 Calling file name changed to m8051.vhd
--                      1.001 Original
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s019bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(INTA:            
            out std_logic;
            IE,
            IP:
            out std_logic_vector(7 downto 0);
            VECTOR_ADDR:
            out std_logic_vector(4 downto 1);
            IACK:
            out std_logic_vector(3 downto 0);
            RITI,
            WEP,
            RETI,
            LCYC,
            T_EN,
            S_EN,
            DIV2CK,
            CLEAR,
            RST,
            NX1,
            NX2:
            in std_logic;
            STATD:
            in std_logic_vector(1 downto 1);
            CYC:
            in std_logic_vector(2 downto 2);
            TCON: --even bits not used
            in std_logic_vector(7 downto 1); --even bits not used
            RAMDI:
            in std_logic_vector(7 downto 0);
            SFRW:
            in std_logic_vector(13 downto 12)
            );
end m3s019bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s019bo_rtl of m3s019bo_e is
--*********************************************************************
--*********************************************************************
--signal definition
--*********************************************************************
signal IP0,IP1,L_INTA:std_logic;
signal PRA,PRB,PRC,PRD,PRE,INT_EN:std_logic;
signal AA,AB,AC,AD,AE,AF,AG,AH,AI,AJ,AK,AL,BA,BB:std_logic;
signal L_IE,L_IP:std_logic_vector(7 downto 0);
signal ILA,ILB,ILL,LAT_ILA,LAT_ILB:std_logic_vector(4 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions 
--*********************************************************************
misc1:process(L_IE,STATD,PRA,PRB,PRC,PRD,PRE,ILA,ILB,ILL,CYC,L_INTA)
begin
   AA <= L_IE(0) and L_IE(7) and PRA;
   AB <= L_IE(1) and L_IE(7) and PRB;
   AC <= L_IE(2) and L_IE(7) and PRC;
   AD <= L_IE(3) and L_IE(7) and PRD;
   AE <= L_IE(4) and L_IE(7) and PRE;
   AF <= ILA(0) or ILA(1) or ILA(2) or ILA(3) or ILA(4);
   AG <= ILB(0) or ILB(1) or ILB(2) or ILB(3) or ILB(4);
   AH <= ILL(1) and not ILL(0);
   AI <= ILL(2) and not(ILL(1) or ILL(0));
   AJ <= ILL(3) and not(ILL(2) or ILL(1) or ILL(0));
   AK <= ILL(4) and not(ILL(3) or ILL(2) or ILL(1) or ILL(0));
   AL <= STATD(1) and CYC(2) and L_INTA;
end process misc1;
--*********************************************************************
misc2:process(WEP,RETI,IP0,IP1,AF,AG)
begin
   BA <= WEP or RETI or IP1 or  not AG; 
   BB <= WEP or RETI or IP1 or IP0 or AG or not AF; 
end process misc2;
--*********************************************************************
priorlevelsel:process(NX1,RST)
begin
   if RST ='1' then
           PRA <= '0';
           PRB <= '0';
           PRC <= '0';
           PRD <= '0';
           PRE <= '0';
   elsif (NX1'event and NX1 ='1') then
       if (((not DIV2CK) and S_EN) = '1') then
           PRA <= TCON(1);
           PRB <= TCON(5);
           PRC <= TCON(3);
           PRD <= TCON(7);
           PRE <= RITI;
        end if;
    end if;
end process priorlevelsel;     
--********************************************************************* 
intprior_0:process (L_IP,AA,AB,AC,AD,AE)
begin
   ILA(0) <= AA and not L_IP(0);
   ILA(1) <= AB and not L_IP(1);
   ILA(2) <= AC and not L_IP(2);
   ILA(3) <= AD and not L_IP(3);
   ILA(4) <= AE and not L_IP(4);
end process intprior_0;
--*********************************************************************
intprior_1:process (L_IP,AA,AB,AC,AD,AE)
begin
   ILB(0) <= AA and L_IP(0);
   ILB(1) <= AB and L_IP(1);
   ILB(2) <= AC and L_IP(2);
   ILB(3) <= AD and L_IP(3);
   ILB(4) <= AE and L_IP(4);
end process intprior_1;
--*********************************************************************
setint_en:process(NX1,RST)
begin
   if RST = '1' then
       INT_EN <= '0';
   elsif (NX1'event and NX1 ='1') then
       if DIV2CK = '1' then
           INT_EN <= T_EN;
       end if;
   end if;
end process setint_en;
--*********************************************************************
setip1:process(NX1)
begin
   if (NX1'event and NX1 ='1') then
       if (CLEAR ='1') then
          IP1 <= '0';
       elsif (INT_EN and DIV2CK) ='1' then
          if ((RETI or not IP1) = '1') then
              IP1 <= LCYC and not BA;
          end if;
       end if;
    end if;
end process setip1;
--*********************************************************************
setip0:process(NX1)
begin
   if (NX1'event and NX1 ='1') then
      if (CLEAR ='1') then
         IP0 <= '0';
      elsif (INT_EN and DIV2CK) ='1' then
         if (((RETI and (not LCYC) and not IP1) or not(IP0 or IP1)) = '1') then
              IP0 <= LCYC and not BB;
          end if;
       end if;
    end if;
end process setip0;
--*********************************************************************
setlilx:process(NX1)
begin
   if (NX1'event and NX1 ='1') then
       if (INT_EN and LCYC and DIV2CK) ='1' then
           LAT_ILA <= ILA;
           LAT_ILB <= ILB;
       end if;
    end if;
end process setlilx;
--*********************************************************************
setill:process(LAT_ILA,LAT_ILB,IP1)
begin
   if IP1 = '0' then
      ILL <= LAT_ILA;
   else
      ILL <= LAT_ILB;
   end if;   
end process setill;
--*********************************************************************
--outputs and directly related
--*********************************************************************
setie:process(NX2)
begin
   if (NX2'event and NX2 ='1') then
       if (CLEAR ='1') then
          L_IE <= "00000000";
       elsif (SFRW(12) ='1') then
          L_IE <= RAMDI;
       end if;
   end if;
end process setie;
--*********************************************************************
setip:process(NX2)
begin
   if (NX2'event and NX2 ='1') then
       if (CLEAR ='1') then
          L_IP <= "00000000";
       elsif (SFRW(13) ='1') then
          L_IP <= RAMDI;
       end if;
   end if;
end process setip;
--********************************************************************* 
localout:process(L_IE,L_IP,L_INTA)
begin
   IE  <= L_IE;
   IP <= L_IP;
   INTA <= L_INTA;
end process localout;
--*********************************************************************
setinta:process(NX1,RST)
begin
   if RST = '1' then
       L_INTA <= '0';
   elsif (NX1'event and NX1 ='1') then
       if (CLEAR ='1') then
          L_INTA <= '0';
       elsif ((INT_EN and DIV2CK and  LCYC)='1') then
          L_INTA <= not(BA and BB);
       end if;
    end if;
end process setinta;
--*********************************************************************
hardintack:process(CLEAR,AL,ILL,AH,AI,AJ)
begin
   if CLEAR ='1' then
      IACK <= "0000";
   elsif AL = '0' then
      IACK <= "1111";
   else
      IACK(0) <= not ILL(0);
      IACK(1) <= not AH;
      IACK(2) <= not AI;
      IACK(3) <= not AJ;
   end if;
end process hardintack;      
--*********************************************************************
intvect:process(AH,AI,AJ,AK,IP0,IP1)
begin
   VECTOR_ADDR(1) <= IP0 or IP1;
   VECTOR_ADDR(2) <= AH or AJ;
   VECTOR_ADDR(3) <= AI or AJ;
   VECTOR_ADDR(4) <= AK;
end process intvect;
--*********************************************************************
end m3s019bo_rtl;
--*********************************************************************
