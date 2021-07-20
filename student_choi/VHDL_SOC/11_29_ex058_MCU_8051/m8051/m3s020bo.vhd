--Miscellaneous Special Function Registers for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.006
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s020bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       29th Nov 1995
--Purpose       :       misc registers inc stack pointer for M8051
--Version       :       1.006
--Mod Date      :       20th March 1997
--Mod History	:       1.006 STATD(7-12) and DIV2CK1 removed
--                      1.005 Parity flag write timing corrected.
--                      1.004 ECN 878: Carry updated in cycle 2 for CJNE
--                            instructions, redundancy removed from
--                            PSWDAT(7) and PSWC.  Sensitivity list
--                            revisions.  XROM moved to m3s010bo.
--                      1.003 Idle Mode Power Saving
--			1.002 Calling file name changed to m8051
--                      1.001 Original
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :m3s014bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s020bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(RESINT:            
            out std_logic;
            SP,
            PCON,
            PSWDAT,
            MSIZ:
            out std_logic_vector(7 downto 0);
            CO,
            ACO,
            OV,
            PAR,
            DAA,
            CJNE,
            OPLOAD,
            MULDIV,
            INTA,
            LCYC,
            DIV2CK2,
            CLEAR,
            RST,
	    STATE12,
            NX1,
            NX2:
            in std_logic;
            CYC:
            in std_logic_vector(2 downto 1);
            PSWC:
            in std_logic_vector(2 downto 0);
            SPC:
            in std_logic_vector(3 downto 0);
            STATD:
            in std_logic_vector(6 downto 1);
            RAMDI:
            in std_logic_vector(7 downto 0);
            SFRW:
            in std_logic_vector(19 downto 16)
             );
end m3s020bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s020bo_rtl of m3s020bo_e is
--*********************************************************************
--*********************************************************************
-- Component Definitions
--*********************************************************************
--Stack Pointer
component m3s014bo_e
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
end component;
--*********************************************************************
--*********************************************************************
--signal definition
--*********************************************************************
signal L_RESINT:std_logic;
signal AA:std_logic;
signal ENAB:std_logic;
signal L_MSIZ:std_logic_vector(7 downto 0);
signal L_PCON:std_logic_vector(1 downto 0);
--*********************************************************************
--*********************************************************************
--port mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s014bo_e
  port map(
           SP => SP,
           RAMDI => RAMDI,
           SPC(1 downto 0) => SPC(1 downto 0),
           SFRW(16 downto 16) => SFRW(16 downto 16),
           DIV2CK => DIV2CK2,
           NX1 => NX2,
           CLEAR =>CLEAR,
           ENAB =>ENAB
           );
--*********************************************************************

--*********************************************************************
--Process Definitions 
--*********************************************************************
misc1:process(STATD,SPC)
begin
    AA <= (STATD(2) and SPC(1)) or (STATD(5) and SPC(0)); 
end process misc1;

--*********************************************************************
setenab:process(AA,CYC,SPC,L_RESINT,SFRW)
begin
    ENAB <= ((AA and not L_RESINT) and ((SPC(2)and CYC(1)) or (SPC(3)and CYC(2)))) or SFRW(16);
end process setenab;
--*********************************************************************

--*********************************************************************
--outputs and directly related
--*********************************************************************
setpconhi:process(NX2,RST)
begin
   if RST ='1' then
      PCON(7 downto 2) <= "000000";
   elsif (NX2'event and NX2 ='1') then
      if SFRW(18) ='1' then
         PCON(7 downto 2) <= RAMDI(7 downto 2);
      end if;
   end if;
end process setpconhi;
--*********************************************************************
setpconlo:process(NX1,RST)
begin
   if RST ='1' then
      L_PCON(1 downto 0) <= "00";
   elsif (NX1'event and NX1 ='1') then
       if ((STATE12 and INTA) ='1') then
          L_PCON(1 downto 0) <= "00";
       elsif SFRW(18) ='1' then
          L_PCON(1 downto 0) <= RAMDI(1 downto 0);
       end if;
   end if;
end process setpconlo;
--*********************************************************************
setpsw:process(NX2)
begin
   if (NX2'event and NX2 ='1') then
       if (CLEAR ='1') then
          PSWDAT(7 downto 0) <="00000000"; 
       else
          if SFRW(17) ='1' then
             PSWDAT(1) <= RAMDI(1);
             PSWDAT(5 downto 3) <= RAMDI(5 downto 3);
          end if;
          if (STATD(6) and LCYC and not DIV2CK2)='1' then 
             if  SFRW(17) ='1' then
                 PSWDAT(2) <= RAMDI(2);
                 PSWDAT(6) <= RAMDI(6);
                 PSWDAT(7) <= RAMDI(7);
             else
                 if PSWC(0) ='1' then
                    PSWDAT(2) <= OV;
                 end if;
                 if PSWC(1) ='1' then
                    PSWDAT(6) <= ACO;
                 end if;
                 if PSWC(2) ='1' then
                    PSWDAT(7) <= (CO and not MULDIV);
                 end if;
             end if;
          end if;
          -- load parity flag at C1S1P1 of every instruction
          if (STATD(1) and DIV2CK2 and CYC(1)) = '1' then
             PSWDAT(0) <= PAR;
          end if;
          if (STATD(3) and not DIV2CK2 and (DAA or (CYC(2) and CJNE)))
             = '1' then
             PSWDAT(7) <= CO;
          end if;
       end if;
    end if;
end process setpsw;
--********************************************************************* 
setmsiz:process(NX2)
begin
   if (NX2'event and NX2 ='1') then
       if (CLEAR ='1') then
          L_MSIZ <= "00001111";
       elsif SFRW(19) = '1' then
          L_MSIZ <= RAMDI;
       end if;
   end if;
end process setmsiz;
--********************************************************************* 
-- setxrom:process(PCH,L_MSIZ)
-- begin
--    if PCH > L_MSIZ then
--        XROM <= '1';
--    else
--        XROM <= '0';
--    end if; 
-- end process setxrom;
--********************************************************************* 
localout:process(L_RESINT,L_MSIZ,L_PCON)
begin
   RESINT <= L_RESINT;
   MSIZ <= L_MSIZ;
   PCON (1 downto 0) <= L_PCON;
end process localout;
--*********************************************************************
setresint:process(NX2)
begin
   if (NX2'event and NX2 ='1') then
      if CLEAR = '1' then
          L_RESINT <= '1';
      elsif OPLOAD = '1' then
          L_RESINT <= '0';
      end if;
    end if;
end process setresint;   
--*********************************************************************
end m3s020bo_rtl;
--*********************************************************************

