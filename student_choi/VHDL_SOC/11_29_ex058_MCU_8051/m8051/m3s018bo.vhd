--Port Controller and Registers for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights Reserved.
--v1.010
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s018bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       17th Nov 1995
--Purpose       :       Port Control for M8051
--Version       :       1.010
--Mod Date      :       14th April 1997
--Mod History	:       1.010 Port 0 output MUX controls re-written.
--                            Redundant signals removed.
--                      1.009 Name changes and sensitivity list
--                            revisions.
--                            Program address bus revisions.
--                      1.008 ECN 878: revised SFR writeback time.
--                            SFR write time moved to end of S6P2 and
--                            redundant SFR relay flip-flops deleted.
--                            No external timing change results.
--                            EXT_PROG_EN moved to m3s010bo.
--                      1.007 Port initialisation during reset
--                      1.006 Idle Mode Power Saving
--                      1.005 Change for reset compatibility and
--                            OPH and OPL changed to DPH and DPL
--                            ECN 865 Fix for external idle mode;
--                      1.004 Fix to match dummy address fetches
--                      1.003 ECN 837 Fix for movc high byte 
--                      1.002 Calling file name changed to m8051.vhd
--                      1.001 Original
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :None
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s018bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ALE,
            NPSEN,
            MOEI,
            EXPMEM:
            out std_logic;
            OAI,
            OB,
            OC,
            OD,
            AE,
            BE,
            CE,
            DE,
            PORTA,
            PORTB,
            PORTC,
            PORTD:
            out std_logic_vector(7 downto 0);
            PROGRAM_ADDR:
            in std_logic_vector(15 downto 0);
            AI,
            BI,
            CI,
            DI,
            RAMDI,
            DPL,
            DPH,
            ACCDAT,
            FA:
            in std_logic_vector(7 downto 0);
            STATD:
            in std_logic_vector(6 downto 1);
            MOVX:
            in std_logic_vector(4 downto 0);
            SFRW:
            in std_logic_vector(3 downto 0);
            CYC:
            in std_logic_vector(2 downto 1);
            PCON:
            in std_logic_vector(0 downto 0);
            XROM,
            EXT_PROG_EN,
            NEA,
            RXDO,
            TXDO,
            RMW,
            DIV2CK,
            NX1,
            NX2,
            CLEAR,
            RST,
            DLMR:
            in std_logic
            );
end m3s018bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s018bo_rtl of m3s018bo_e is
--*********************************************************************


--*********************************************************************
--signal definition
--*********************************************************************
signal AA:std_logic;
signal L_EXPMEM,POPMEN,PODMEN,P0DADD,AEEN,EXTDAT,IDLE:std_logic;
signal QALE,NQEN,NRD,NWR,SELC, EXTEND_MOVX:std_logic;
signal LOCALC, LOCALE, LOCALF, LOCALH:std_logic_vector(7 downto 0);
signal PORT0_SFR, PORT1_SFR, PORT2_SFR, PORT3_SFR: std_logic_vector(7 downto 0);
signal L_OC, L_OD:std_logic_vector(7 downto 0);
signal LAI_IN, LBI_IN, LCI_IN, LDI_IN:std_logic_vector(7 downto 0);
signal SELA:std_logic_vector(2 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions 
--*********************************************************************
misc1:process(STATD, MOVX, CYC)
begin
    AA <= STATD(3) or (STATD(6) and not(MOVX(0) and CYC(2)));
end process misc1;
--*********************************************************************
misc2:process(PODMEN, POPMEN, DLMR)
begin
    AEEN <= PODMEN or POPMEN or DLMR;
end process misc2;
--*********************************************************************
misc4:process(NX2,RST)
begin
    if RST = '1' then
       L_EXPMEM <= '0';
    elsif NX2'event and NX2 = '1' then
       if DIV2CK = '1' then
          L_EXPMEM <= EXT_PROG_EN;
       end if;
    end if;
end process misc4;
--*********************************************************************
setale:process(NX2,RST)
-- ALE runs continously regardless of whether program memory read is
-- internal or external.  Ale is only suspended by MOVX instructions.
begin
    if RST = '1' then
       QALE <= '1';
    elsif NX2'event and NX2 ='1' then  
       if DIV2CK ='1' then 
           QALE <= STATD(4) or (STATD(1) and not(MOVX(0) and CYC(2))) or (CLEAR and not STATD(5));
       end if;
    end if;    
end process setale;
--*********************************************************************
setpopmen:process(NX2)
begin
    if NX2'event and NX2 = '1' then
       if DIV2CK ='0' then
           POPMEN <= (XROM or not NEA) and ((STATD(1) and not CLEAR and
                      not(MOVX(0) and CYC(2)))
                     or (STATD(4) and not(MOVX(0) and CYC(1)))) and
                     not RST;
       end if ;
     end if;
end process setpopmen;
--*********************************************************************
set_port_sfrs:process(NX2, RST)
-- set port SFRs at end of S6P2.
-- Port 0 SFR is set to ones by certain external memory operations.
begin
   if RST = '1' then
      PORT0_SFR <= "11111111";
      PORT1_SFR <= "11111111";
      PORT2_SFR <= "11111111";
      PORT3_SFR <= "11111111";
   elsif NX2'event and NX2 = '1' then
      if DIV2CK ='0' then
         if (((EXT_PROG_EN or MOVX(0)) and AA) ='1') then
            PORT0_SFR <= "11111111";
         elsif SFRW(0) ='1' then PORT0_SFR <= RAMDI;
         end if;
         if SFRW(1) ='1' then PORT1_SFR <= RAMDI;
         end if;
         if SFRW(2) ='1' then PORT2_SFR <= RAMDI;
         end if;
         if SFRW(3) ='1' then PORT3_SFR <= RAMDI;
         end if;
      end if; -- not DIV2CK
   end if; -- NX2 event
end process set_port_sfrs;      
--*********************************************************************
setlocalc:process(NX2,RST)   
-- delay port enable switch offs by two clocks to beginning of S2P1
begin
   if RST = '1' then
      LOCALC <= "11111111";
   elsif NX2'event and NX2 = '1' then
      if ( STATD(1) and not DIV2CK ) ='1' then
         LOCALC <= PORT1_SFR;
      end if;
   end if;
end process setlocalc;  
--********************************************************************* 
muxlocale:process(DPH,PROGRAM_ADDR,EXTDAT)
begin
   case EXTDAT is
       when '0' => LOCALE <= PROGRAM_ADDR(15 downto 8);
       when '1' => LOCALE <= DPH;
       when others => LOCALE <= "XXXXXXXX";
    end case;
end process muxlocale;
--*********************************************************************
setlocalf:process(NX2,RST)   
-- Delayed enable for port 2 derived from multiplexed port 2 output,
-- not the raw port 2 SFR contents.
begin
    if RST = '1' then
        LOCALF <= "11111111";
    elsif NX2'event and NX2 = '1' then
        if DIV2CK ='0' then
           if (STATD(1) or (STATD(5) and not SELC)) ='1' then
               LOCALF <=L_OC;
           end if;
         end if;
     end if;
end process setlocalf;  
--********************************************************************* 
setlocalh:process(NX2,RST)
begin
    if RST = '1' then
       LOCALH <= "11111111";
    elsif NX2'event and NX2 = '1' then       
       if DIV2CK ='0' then
           LOCALH <= L_OD;
       end if;
    end if;
end process setlocalh;      
--*********************************************************************
setextdat:process(NX2)
begin
    if NX2'event and NX2 = '1' then
       if CLEAR = '1' then
             EXTDAT <= '0';
       elsif DIV2CK = '0' then
          if ((STATD(4) and CYC(1) and MOVX(0)) ='1') then
             EXTDAT <= '1';
          elsif ((STATD(4) and CYC(2)) ='1') then
             EXTDAT <= '0';
          end if;
       end if;
    end if;
end process setextdat;
--*********************************************************************
setpodmen:process(NX2)
begin
    if NX2'event and NX2 = '1' then
       if DIV2CK = '0' then
          if ((STATD(4) and CYC(1) and MOVX(0)) ='1') then
             PODMEN <= '1';
          elsif ((STATD(4) and CYC(2)) or CLEAR or
                (MOVX(4) and STATD(5) and EXTDAT)) = '1' then
             PODMEN <= '0';
          end if;
        end if;
     end if;
end process setpodmen;
--*********************************************************************
setaddmen:process(NX2)
begin
    if NX2'event and NX2 = '1' then
       if CLEAR = '1' then
          P0DADD <= '0';
       elsif DIV2CK = '0' then
          if ((STATD(4) and CYC(1) and MOVX(0)) ='1') then
             P0DADD <= '1';
          end if;
       elsif DIV2CK ='1' then
          if (STATD(6) ='1') then
             P0DADD <= '0';
          end if;
       end if;
     end if;
end process setaddmen;
--*********************************************************************
latportin:process(NX2)
begin
  if NX2'event and NX2 = '1' then
       if DIV2CK ='0' then
          if STATD(4) ='1' then
             LAI_IN <= AI;
             LBI_IN <= BI;
             LCI_IN <= CI;
             LDI_IN <= DI;
           end if;
        end if;
   end if;
end process latportin;
--*********************************************************************
--External signals+directly related
--*********************************************************************
set_hlt:process(NX1,RST)
begin
    if RST = '1' then
        IDLE <= '0';
    elsif NX1'event and NX1 ='1' then
        IDLE <= PCON(0);
    end if;
end process set_hlt;
--*********************************************************************
setouts:process(NQEN,L_EXPMEM,IDLE,MOVX,PORT1_SFR,L_OC,L_OD)
begin
    NPSEN <= IDLE or NQEN or not L_EXPMEM;
    MOEI <= not (L_EXPMEM or NQEN);
    EXPMEM <= L_EXPMEM;
    OB <= PORT1_SFR;
    OC <= L_OC;
    OD <= L_OD;
end process setouts;
--*********************************************************************
aleout:process(QALE,IDLE)
begin
          ALE <= IDLE or QALE;
end process aleout;
--*********************************************************************
setqen:process(NX2,RST)
begin
    if RST = '1' then
       NQEN <= '1';
    elsif NX2'event and NX2 ='1' then
       if DIV2CK = '0' then
          if ((STATD(5) and not(CYC(1) and MOVX(0))) or 
             (STATD(2) and not CLEAR and not(CYC(2) and MOVX(0)))) = '1'
          then
                NQEN <= '0';
          end if;
       else
          if (STATD(1) or STATD(4)) = '1' then
                NQEN <= '1';
          end if;
       end if;
    end if;
end process setqen;
--*********************************************************************
setselc:process(MOVX, EXTDAT, EXT_PROG_EN,RST)
begin
   SELC <= (MOVX(2) and EXTDAT) or
           (EXT_PROG_EN and not EXTDAT and not RST);
end process setselc;
--*********************************************************************
stretch_movx: process(NX2)
-- Extend MOVX write timing on Port 0 by one clock period for exact
-- compatibility with discrete devices.
begin
   if NX2'event and NX2 = '1' then
      EXTEND_MOVX <= STATD(4) and MOVX(3);
   end if;
end process stretch_movx;
--*********************************************************************
setselmuxoa:process(EXTDAT, EXTEND_MOVX, EXT_PROG_EN, P0DADD, MOVX, CYC)
-- Port 0 output data source control.
-- Concatenate MUX select inputs for benefit of case syntax.
-- Default condition is 110, i.e. output port 0 SFR contents.
begin 
   SELA(2 downto 0) <=((EXTEND_MOVX and CYC(2)) or not EXTDAT)
                      &
                      ((EXTDAT or not EXT_PROG_EN)
                      and not EXTEND_MOVX and not P0DADD)
                      &
                      MOVX(1);
end process setselmuxoa;
--*********************************************************************
muxoa:process(SELA,DPL,FA,ACCDAT,PROGRAM_ADDR,PORT0_SFR)
-- Port 0 output data source multiplexer
begin
   case SELA(2 downto 0) is
       when "000" => OAI <= DPL;
       when "001" => OAI <= FA;
       when "010" => OAI <= ACCDAT;
       when "011" => OAI <= ACCDAT;
       when "100" => OAI <= PROGRAM_ADDR(7 downto 0);
       when "101" => OAI <= PROGRAM_ADDR(7 downto 0);
       when "110" => OAI <= PORT0_SFR;
       when "111" => OAI <= PORT0_SFR;
       when others => OAI <= "XXXXXXXX";
    end case;
end process muxoa;
--*********************************************************************
muxoc:process(SELC,PORT2_SFR,LOCALE)
begin
   case SELC is
       when '0' => L_OC <= PORT2_SFR;
       when '1' => L_OC <=  LOCALE;
       when others => L_OC <= "XXXXXXXX";
    end case;
end process muxoc;
--*********************************************************************
setodrest:process(RXDO, TXDO, NWR, NRD, PORT3_SFR)
-- Wire-OR alternate function outputs onto port 3 output pins.
begin
    L_OD(0) <= PORT3_SFR(0) and RXDO; 
    L_OD(1) <= PORT3_SFR(1) and TXDO; 
    L_OD(2) <= PORT3_SFR(2);
    L_OD(3) <= PORT3_SFR(3);
    L_OD(4) <= PORT3_SFR(4);
    L_OD(5) <= PORT3_SFR(5);
    L_OD(6) <= PORT3_SFR(6) and NWR; 
    L_OD(7) <= PORT3_SFR(7) and NRD; 
end process setodrest;  
--*********************************************************************
movx_strobes:process(NX2)
-- Generate MOVX read and write strobes, between end S6P2 and end S3P2.
begin
    if NX2'event and NX2 = '1' then
       if DIV2CK ='0' then
          if (STATD(3) or CLEAR) = '1' then
             NWR <= '1';
             NRD <= '1';
          elsif ((STATD(6) and CYC(1)) ='1') then
             NWR <= not MOVX(3);
             NRD <= not MOVX(4);
          end if;
        end if;
     end if;
end process movx_strobes;
--*********************************************************************
setae:process(AEEN,PORT0_SFR)
begin
    if AEEN ='1' then
       AE <= "00000000";
    else
       AE <= PORT0_SFR;
    end if;
end process setae;
--********************************************************************* 
setbe:process(PORT1_SFR,LOCALC)
begin
    BE(0) <= PORT1_SFR(0) and LOCALC(0);
    BE(1) <= PORT1_SFR(1) and LOCALC(1);
    BE(2) <= PORT1_SFR(2) and LOCALC(2);
    BE(3) <= PORT1_SFR(3) and LOCALC(3);
    BE(4) <= PORT1_SFR(4) and LOCALC(4);
    BE(5) <= PORT1_SFR(5) and LOCALC(5);
    BE(6) <= PORT1_SFR(6) and LOCALC(6);
    BE(7) <= PORT1_SFR(7) and LOCALC(7);
end process setbe;  
--********************************************************************* 
setce:process(L_OC,LOCALF,SELC)
begin
    CE(0) <= L_OC(0) and LOCALF(0) and not SELC;
    CE(1) <= L_OC(1) and LOCALF(1) and not SELC;
    CE(2) <= L_OC(2) and LOCALF(2) and not SELC;
    CE(3) <= L_OC(3) and LOCALF(3) and not SELC;
    CE(4) <= L_OC(4) and LOCALF(4) and not SELC;
    CE(5) <= L_OC(5) and LOCALF(5) and not SELC;
    CE(6) <= L_OC(6) and LOCALF(6) and not SELC;
    CE(7) <= L_OC(7) and LOCALF(7) and not SELC;
end process setce;  
--********************************************************************* 
setde:process(L_OD, LOCALH)
begin
    DE(0) <= L_OD(0) and LOCALH(0);
    DE(1) <= L_OD(1) and LOCALH(1);
    DE(2) <= L_OD(2) and LOCALH(2);
    DE(3) <= L_OD(3) and LOCALH(3);
    DE(4) <= L_OD(4) and LOCALH(4);
    DE(5) <= L_OD(5) and LOCALH(5);
    DE(6) <= L_OD(6) and LOCALH(6);
    DE(7) <= L_OD(7) and LOCALH(7);
end process setde;
--********************************************************************* 
muxportsin:process(RMW, LAI_IN, PORT0_SFR, LBI_IN, PORT1_SFR, LCI_IN, PORT2_SFR, LDI_IN, PORT3_SFR)
-- PORT SFR read back MUX:  Port pin values are read unless the 
-- instruction is a read modify write operation in which case the port
-- SFR value is used. 
begin
   case RMW is
      when '0' => PORTA <= LAI_IN;
                  PORTB <= LBI_IN;
                  PORTC <= LCI_IN;
                  PORTD <= LDI_IN;
      when '1' => PORTA <= PORT0_SFR;
                  PORTB <= PORT1_SFR;
                  PORTC <= PORT2_SFR;
                  PORTD <= PORT3_SFR;
      when others => PORTA <= "XXXXXXXX";
                     PORTB <= "XXXXXXXX";
                     PORTC <= "XXXXXXXX";
                     PORTD <= "XXXXXXXX";
   end case;
end process muxportsin;
--********************************************************************* 
end m3s018bo_rtl;
--*********************************************************************
