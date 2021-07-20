--Timer Counters for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.005
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s015bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       24th Oct 1995
--Purpose       :       Timer Counter for M8051
--Version       :       1.005
--Mod Date      :       9th April 1997
--                      1.005 Redundant signals removed, name change,
--                            re-load false path removed.
--                      1.004 Overflow synchronising flip-flops
--                            re-instated, TH0 clock source fix,
--                            timer 1 enable logic,
--                            external interrupt sampling flip-flops,
--                            RMW instructions prevented from erasing
--                            pending timer interrupts.
--                            Level sensitive interrupts now sampled
--                            and registered at end of S5P2.
--                            Sensitivity list revisions.
--			1.003 Idle Mode Power Saving.
--			1.002 Calling file name changed to m8051.vhd
--                      1.001 Original
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :m3s016bo.vhd
--                      :m3s017bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;
--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s015bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(LOV1:
            out std_logic;
            TCON,
            TMOD,
            TLA,
            TLB,
            THA,
            THB:
            out std_logic_vector(7 downto 0);
            IACK:
            in std_logic_vector(3 downto 0);
            DI:
            in std_logic_vector(5 downto 2);
            STATD:
            in std_logic_vector(6 downto 6);
            RAMDI:
            in std_logic_vector(7 downto 0);
            SFRW:
            in std_logic_vector(9 downto 4);
            RMW,
            S_EN,
            T_EN,
            STATE12,
            DIV2CK1,
            NX1,
            NX2,
            CLEAR:
            in std_logic
            );
end m3s015bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s015bo_rtl of m3s015bo_e is
--*********************************************************************
--*********************************************************************
-- Component Definition
--*********************************************************************
--8 bit loadable counter with carry out from fifth or eighth bit.
component m3s016bo_e
       port(
            CO:            
            out std_logic;
            CNT:
            out std_logic_vector(7 downto 0);
            MODE0,
            LD,
            CI,
            CLEAR,
            COUNT_EN,
            NX1:
            in std_logic;
            DIN:
            in std_logic_vector(7 downto 0)
            );
end component;
--*********************************************************************
--signal definition
--*********************************************************************
signal COH0,COH1,COL0,COL1,CIH0,CIH1,CIL0,CIL1,MODL0,MODL1:std_logic;
signal INT0PIN,INT1PIN:std_logic;
signal T0L_EN,T0H_EN,T1_EN, OV1_EN, CNT0,CNT1,T0_MODE3,T1_MODE3:std_logic;
signal LOAD0,LOAD1,ILOV0,ILOV1:std_logic;
signal LTCON0,LTCON1,LTCON2,LTCON3,LTCON4,LTCON6:std_logic;
signal TCON1SET,TCON3SET:std_logic;
signal Q7,Q8,Q9,Q10:std_logic;
signal AB,AC:std_logic;
signal LTMOD,LTHA,LTHB,DINA,DINB:std_logic_vector(7 downto 0);
signal COUNTER0_EN, COUNTER1_EN,TIMER0_EN,TIMER1_EN,TIMERS_EN:std_logic;
signal LOV0, LLOV1: std_logic; -- synchronised timer overflow registers
signal INT0, INT1: std_logic; -- sampled external interrupt inputs
signal OLD_INT0, OLD_INT1: std_logic; -- external interrupt memories
signal LOGIC0: std_logic;

--*********************************************************************
--*********************************************************************
--port mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s016bo_e --Timer zero high byte
  port map(
           CO => COH0,           
           CNT => LTHA,
           MODE0 => LOGIC0,
           LD =>  SFRW(8),
           CI => CIH0,
           CLEAR => CLEAR,
           COUNT_EN => T0H_EN,
           NX1 => NX1,
           DIN => RAMDI
           );
--*********************************************************************
U2:m3s016bo_e --Timer one high byte
  port map(
           CO => COH1,           
           CNT => LTHB,
           MODE0 => LOGIC0,
           LD =>  SFRW(9),
           CI => CIH1,
           CLEAR => CLEAR,
           COUNT_EN => T1_EN,
           NX1 => NX1,
           DIN => RAMDI
           );
--*********************************************************************
U3:m3s016bo_e -- Timer zero low byte
  port map(
           CO => COL0,           
           CNT => TLA,
           MODE0 => MODL0,
           LD => LOAD0,
           CI => CIL0,
           CLEAR => CLEAR,
           COUNT_EN => T0L_EN,
           NX1 => NX1,
           DIN => DINA
           );
--*********************************************************************
U4:m3s016bo_e -- Timer one low byte
  port map(
           CO => COL1,           
           CNT => TLB,
           MODE0 => MODL1,
           LD => LOAD1,
           CI => CIL1,
           CLEAR => CLEAR,
           COUNT_EN => T1_EN,
           NX1 => NX1,
           DIN => DINB
           );
--*********************************************************************

--*********************************************************************
--Process Definitions 
--*********************************************************************
tconeven:process(NX2)
begin
    if NX2'event and NX2 ='1' then
        if CLEAR ='1' then
            LTCON0 <= '0';
            LTCON2 <= '0';
            LTCON4 <= '0';
            LTCON6 <= '0';
        elsif SFRW(4) = '1' then
            LTCON0 <= RAMDI(0);
            LTCON2 <= RAMDI(2);
            LTCON4 <= RAMDI(4);
            LTCON6 <= RAMDI(6);           
        end if;
    end if;
end process tconeven;
--*********************************************************************
gen1:process(LTMOD)
begin
   AB <= LTMOD(4) or (LTMOD(0) and LTMOD(1)) or not LTMOD(5);
   AC <= LTMOD(5) or (LTMOD(0) and LTMOD(1));
end process gen1;
--*********************************************************************
tconodd:process(NX1)
-- TCON odd bits may be set at S5P2 by interrupt sources
-- Interrupts may be overwritten by direct register load instructions,
-- but not by read-modify-write instructions.
begin
    if NX1'event and NX1 ='1' then
       if CLEAR ='1' then 
           LTCON1 <='0';
           LTCON3 <='0';
           TCON(5) <='0';
           TCON(7) <='0';
       else 
           if IACK(0) ='0' then
                LTCON1 <= '0';
           elsif TCON1SET ='1' then
                LTCON1 <= '1';
           elsif SFRW(4) = '1' then
                LTCON1 <= RAMDI(1);
           end if;

           if IACK(2) ='0' then
                LTCON3 <= '0';
           elsif TCON3SET ='1' then
                LTCON3 <= '1';
           elsif SFRW(4) = '1' then
                LTCON3 <= RAMDI(3);
           end if; 

           if IACK(1) ='0' then
                 TCON(5) <= '0';
           elsif DIV2CK1 = '0' then
              if (LOV0  and (S_EN or (RMW and STATD(6)))) = '1' then
                 TCON(5) <= '1';
              elsif SFRW(4) = '1' then
                 TCON(5) <= RAMDI(5);
              end if;
           end if; 


           if IACK(3) ='0' then
              TCON(7) <= '0';
           elsif DIV2CK1 = '0' then
              if  (LLOV1 and (S_EN or (RMW and STATD(6)))) = '1' then
                 TCON(7) <= '1';
              elsif SFRW(4) = '1' then
                 TCON(7) <= RAMDI(7);
              end if; 
           end if; 
       end if;
    end if;
end process tconodd;
--*********************************************************************
selecttcon1:process(LTCON0,LTCON1,INT0, OLD_INT0)
begin
   case LTCON0 is
       when '0' => TCON(1) <= INT0 or OLD_INT0;
       when '1' => TCON(1) <= LTCON1;
       when others => TCON(1) <= 'X';
    end case;
end process selecttcon1;   
--*********************************************************************
selecttcon3:process(LTCON2,LTCON3,INT1, OLD_INT1)
begin
   case LTCON2 is
       when '0' => TCON(3) <= INT1 or OLD_INT1;
       when '1' => TCON(3) <= LTCON3;
       when others => TCON(3) <= 'X';
    end case;
end process selecttcon3;   
--*********************************************************************
tconctrl1:process(NX1)
-- External interrupt sampling flip-flops
begin
    if NX1'event and NX1 ='1' then
       if CLEAR='1' then
          INT0 <= '0';
          OLD_INT0 <= '0';
          INT1 <= '0';
          OLD_INT1 <= '0';
       elsif (DIV2CK1='0' and S_EN='1') then
          INT0 <= not DI(2);
          OLD_INT0 <= INT0;
          INT1 <= not DI(3);
          OLD_INT1 <= INT1;
       end if;
    end if;
end process tconctrl1;
--*********************************************************************
tconsetclr:process(INT0, INT1, OLD_INT0, OLD_INT1)
-- External interrupt falling edge detectors
begin 
   TCON1SET <= INT0 and not OLD_INT0;
   TCON3SET <= INT1 and not OLD_INT1;
end process tconsetclr;
--*********************************************************************
synch_ov0: process(NX1) -- convert counter timer 0 carry out to overflow
-- Interrupt source is set at timer oveflow (end of S2P2) and cleared at
-- end of S6P2.
begin
   if NX1'event and NX1 = '1' then
      if T0L_EN = '1' then
         LOV0 <= ILOV0;
      elsif STATE12 = '1' then
         LOV0 <= '0';
      end if;
   end if;
end process synch_ov0;
--*********************************************************************
synch_ov1: process(NX1) -- convert counter timer 1 carry out to overflow
-- Interrupt source is set at timer oveflow (end of S2P2) and cleared at
-- end of S6P2.
begin
   if NX1'event and NX1 = '1' then
      if OV1_EN = '1' then
         LLOV1 <= ILOV1;
      elsif STATE12 = '1' then
         LLOV1 <= '0';
      end if;
   end if;
end process synch_ov1;
--*********************************************************************
settmod:process(NX2)
begin
    if NX2'event and NX2 ='1' then
        if CLEAR ='1' then
            LTMOD(7 downto 0) <= "00000000";
        elsif SFRW(5) = '1' then
            LTMOD(7 downto 0) <= RAMDI(7 downto 0);          
        end if;
    end if;
end process settmod;
--*********************************************************************
set_mods:process(LTMOD)
begin
    MODL0 <= not(LTMOD(0) or LTMOD(1));
    MODL1 <= not(LTMOD(4) or LTMOD(5));
end process set_mods;
--*********************************************************************
intgates:process(NX1)
begin
    if NX1'event and NX1 ='1' then
        if CLEAR ='1' then
            INT0PIN <= '0';
            INT1PIN <= '0';
        elsif (DIV2CK1 = '0') then
            INT0PIN <= DI(2);           
            INT1PIN <= DI(3);           
        end if;
    end if;
end process intgates;
--*********************************************************************
timertims:process(T_EN,DIV2CK1)
begin
       TIMERS_EN <= T_EN and not DIV2CK1;
end process timertims;
--*********************************************************************
timcntenabs:process(T_EN, LTMOD, TIMERS_EN, T1_MODE3, CNT0, CNT1)
-- Timer Counters increment on S3P1 regardless of mode.
-- Timer Counter 1 does not count in mode 3.
begin
   COUNTER0_EN <= TIMERS_EN and LTMOD(2) and CNT0; 
   COUNTER1_EN <= TIMERS_EN and LTMOD(6) and CNT1 and not T1_MODE3; 
   TIMER0_EN <=   TIMERS_EN and not LTMOD(2); 
   TIMER1_EN <=   TIMERS_EN and not LTMOD(6) and not T1_MODE3; 
end process timcntenabs;
--*********************************************************************
timer_en:process(COUNTER0_EN,COUNTER1_EN,TIMER0_EN,TIMER1_EN,TIMERS_EN, T0_MODE3, SFRW)
begin
   T0L_EN <= COUNTER0_EN or TIMER0_EN or SFRW(6);
   T0H_EN <= (not(T0_MODE3) and (COUNTER0_EN or TIMER0_EN)) or 
             (T0_MODE3 and TIMERS_EN) or SFRW(8);
   T1_EN <= COUNTER1_EN or TIMER1_EN or SFRW(7) or SFRW(9);
end process timer_en;
--*********************************************************************
overflow1_en:process(T0H_EN, T1_EN, T0_MODE3)
-- MUX for replacing T1_EN with T0H_EN as clock source for overflow
-- register in mode 3.
begin
   OV1_EN <= (T1_EN and not T0_MODE3) or (T0H_EN and T0_MODE3);  
end process overflow1_en;
--*********************************************************************
set_nci:process(LTMOD, T0_MODE3, LTCON4, LTCON6, INT0PIN, INT1PIN, COL0,
                COL1, STATD)
-- Define carry inputs to the four 8-bit counters.
-- Mask carry inputs during SFR write window (end STATD(6)).
begin
   CIL0 <= LTCON4 and (not(LTMOD(3)) or INT0PIN) and not STATD(6);
   CIL1 <= LTCON6 and (not(LTMOD(7)) or INT1PIN) and not STATD(6);
   CIH0 <= ((COL0 and not LTMOD(1)) or (T0_MODE3 and LTCON6))
           and not STATD(6);
   CIH1 <= COL1 and not LTMOD(5) and not STATD(6); 
end process set_nci;
--*********************************************************************
set_ilov:process(COH0,COL0,COL1,COH1,LTMOD,CLEAR,AB,AC)
begin 
   ILOV0 <= ((COH0 and not LTMOD(1)) or (COL0 and LTMOD(1)))
            and not CLEAR;    
   ILOV1 <= ((COH1 and not AC) or (COL1 and not AB) or(COH0 and LTMOD(0)
            and LTMOD(1))) and not CLEAR;
end process set_ilov;
--*********************************************************************
set_cnt1:process(NX1)-- input edge detector with process set_cnt2 
begin
    if NX1'event and NX1 ='1' then
       if CLEAR ='1' then
          Q7 <= '0';
          Q8 <= '0';
          Q9 <= '0';
          Q10 <= '0';
       elsif (S_EN='1' and DIV2CK1 ='0') then
          Q7 <= DI(4);
          Q8 <= Q7;
          Q9 <= DI(5);
          Q10 <= Q9;
       end if;
     end if;
end process set_cnt1;
--*********************************************************************
set_cnt2:process(Q7,Q8,Q9,Q10)
begin
   CNT0 <= Q8 and not Q7;
   CNT1 <= Q10 and not Q9;
end process set_cnt2;
--*********************************************************************
set_low_byte_load:process(SFRW, LTMOD, COL0, COL1)
-- Low byte counter load control is OR of SFR write signal and in mode 2
-- the low byte overflow.
begin
   LOAD0 <= SFRW(6) or ( LTMOD(1) and not LTMOD(0) and COL0 );
   LOAD1 <= SFRW(7) or ( LTMOD(5) and not LTMOD(4) and COL1 );
end process set_low_byte_load;
--*********************************************************************
set_din:process(RAMDI,LTHA,LTHB,SFRW)
begin
case SFRW(6) is
       when '0' => DINA <= LTHA;
       when '1' => DINA <= RAMDI;
       when others => DINA <= "XXXXXXXX";
    end case;
case SFRW(7) is
       when '0' => DINB <= LTHB;
       when '1' => DINB <= RAMDI;
       when others => DINB <= "XXXXXXXX";
    end case;
end process set_din;
--*********************************************************************
misc1:process(LTMOD)
begin
   T0_MODE3 <= LTMOD(0) and LTMOD(1);
   T1_MODE3 <= LTMOD(4) and LTMOD(5);
end process misc1;
--*********************************************************************
localout:process(LTCON0,LTCON2,LTCON4,LTCON6,LTHA,LTHB,LTMOD,ILOV1,S_EN, LLOV1)
begin
   TCON(0) <= LTCON0;
   TCON(2) <= LTCON2;
   TCON(4) <= LTCON4;
   TCON(6) <= LTCON6;
   THA <= LTHA;
   THB <= LTHB;
   TMOD(7 downto 0) <= LTMOD(7 downto 0);
   LOV1 <= LLOV1 and S_EN;
end process localout;
--*********************************************************************

LOGIC0 <= '0';

--*********************************************************************
end m3s015bo_rtl;
--*********************************************************************
