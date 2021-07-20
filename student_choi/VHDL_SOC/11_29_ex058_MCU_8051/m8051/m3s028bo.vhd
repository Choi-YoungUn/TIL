--UART for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors. All rights reserved.
--v1.009
--*********************************************************************
--%W% %G% SCCS Version Control
--File	        :       m3s028bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       15th Dec 1995
--Purpose       :       UART for M8051
--Version       :       1.009
--Mod Date      :       24th March 1997
--Mod History	:       1.009 Redundant port removed.
--                      1.008 Rename divider carry outputs for Verilog
--                            compatibility.
--                      1.007 UART sampling time and latency fixes.
--                            Sensitivity list revisions.
--                      1.006 Port initialisation during reset
--                      1.005 Idle Mode Power Saving
--			1.004 ECN 812-9 bit mode
--                      1.003-Calling file changed to m8051.vhd
--                            LTCI bus added for verilog conversion, 
--                            no circuit change
--                      1.002-ECNs 742,743
--                      1.001(Original)
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :m3s029bo.vhd
--                      :m3s030bo.vhd
--                      :m3s031bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s028bo_e is 
       port(
            SCON,
            SBUF:
            out std_logic_vector(7 downto 0);
            RITI,
            RXDO,
            TXDO:
            out std_logic;
            DI:
            in std_logic_vector(0 downto 0);
            RAMDI:
            in std_logic_vector(7 downto 0);
            PCON:
            in std_logic_vector(7 downto 7);
            SFRW:
            in std_logic_vector(11 downto 10);
            LOV1,
            S_EN,
            T_EN,
            STATE12,
            DIV2CK1,
            NX1,
            NX2,
            CLEAR:
            in std_logic
            );
end m3s028bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s028bo_rtl of m3s028bo_e is
--*********************************************************************
--*********************************************************************
-- Component Definitions
--*********************************************************************
--1 up bit counter(sync clear)
component m3s029bo_e
       port(CO,
            Q:
            out std_logic;
            CI,
            CLEAR,
            COUNT_EN,
            NX1:
            in std_logic
            );
end component;
--*********************************************************************
--TX shift reg
component m3s030bo_e
       port(SOUT,
            QLOW:
            out std_logic;
            CLEAR,
            NEWDATA,
            TSHIFT_EN,
            TSHIFT_IN,
            NX1:
            in std_logic;
            RAMDI:
            in std_logic_vector(7 downto 0)
            );
end component;
--*********************************************************************
--RX shift reg
component m3s031bo_e
       port(FRM:
            out std_logic_vector(7 downto 0);
            D0,
            LORCV,
            RSHIFT_EN,
            RSHIFT_IN,
            NX1:
            in std_logic
            );
end component;
--*********************************************************************
--signal definition
--*********************************************************************
signal COUNT_EN,TSHIFT_EN,TSHIFT_IN,SOUT:std_logic;
signal RSHIFT_EN,RSHIFT_IN,QLOW,NEWDATA:std_logic;
signal AE,AF,AG,AH:std_logic;
signal TXLASTBIT,TXEND,TISET,RISET:std_logic;
signal DCKM,CKMASK,CLEAR16C_RX,CLEAR16C_TX,MODE0,DIVTWO,MAJOUT,TSEND:std_logic;
signal D0,Q1,Q3,Q5,Q6,Q8,END_DATA:std_logic;
signal TXSTOPBIT,FLST,FSREJ,RXC7,RXC8,RXC9,TXCLK,SETTXCLK:std_logic;
signal RSTQ1,RX_EN,TX_EN,DATAEN,RX_DIN,CLR_RCV,DELCLRRCV:std_logic;
signal RCV,DELRCV,BITIN,SWREC,LORCV,SELRB8,RST16C,DELRST16C,DELCNT:std_logic;
signal MODE0_IN,MAJQ1,MAJQ2,LRITI:std_logic;
signal TCI, RCI, TX_DIV, RX_DIV:std_logic_vector(3 downto 0);
signal LTCI, LRCI:std_logic_vector(3 downto 1);
signal FRM:std_logic_vector(7 downto 0);
signal L_SCON:std_logic_vector(7 downto 3);
signal LL_SCON:std_logic_vector(2 downto 0);
--*********************************************************************
--*********************************************************************
--port mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s029bo_e --MSBit TX generator
  port map(
           CO => open,
           Q => TX_DIV(3),
           CI => TCI(3),
           CLEAR => CLEAR16C_TX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U2:m3s029bo_e -- TX generator
  port map(
           CO => LTCI(3),
           Q => TX_DIV(2),
           CI => TCI(2),
           CLEAR => CLEAR16C_TX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U3:m3s029bo_e -- TX generator
  port map(
           CO => LTCI(2),
           Q => TX_DIV(1),
           CI => TCI(1),
           CLEAR => CLEAR16C_TX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U4:m3s029bo_e --LSBit TX generator
  port map(
           CO => LTCI(1),
           Q => TX_DIV(0),
           CI => TCI(0),
           CLEAR => CLEAR16C_TX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U5:m3s029bo_e --MSBit RX generator
  port map(
           CO => open,
           Q => RX_DIV(3),
           CI => RCI(3),
           CLEAR => CLEAR16C_RX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U6:m3s029bo_e -- RX generator
  port map(
           CO => LRCI(3),
           Q => RX_DIV(2),
           CI => RCI(2),
           CLEAR => CLEAR16C_RX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U7:m3s029bo_e --RX generator
  port map(
           CO => LRCI(2),
           Q => RX_DIV(1),
           CI => RCI(1),
           CLEAR => CLEAR16C_RX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U8:m3s029bo_e --LSBit RX generator
  port map(
           CO => LRCI(1),
           Q => RX_DIV(0),
           CI => TCI(0),
           CLEAR => CLEAR16C_RX,
           COUNT_EN => COUNT_EN,
           NX1 => NX1
           );
--*********************************************************************
U9:m3s030bo_e --TX Buffer
  port map(
           SOUT => SOUT,
           QLOW => QLOW,
           NEWDATA => NEWDATA,
           CLEAR => CLEAR,
           TSHIFT_EN => TSHIFT_EN,
           TSHIFT_IN => TSHIFT_IN,
           NX1 => NX1,
           RAMDI => RAMDI
           );
--*********************************************************************
U10:m3s031bo_e --RX Buffer
  port map(
           FRM => FRM,
           D0 => D0,
           LORCV => LORCV,
           RSHIFT_EN => RSHIFT_EN,
           RSHIFT_IN => RSHIFT_IN,
           NX1 => NX1
           );
--*********************************************************************
--Process Definitions 
--*********************************************************************
setsconhi:process(NX2)
begin
    if NX2'event and NX2 ='1' then
        if CLEAR ='1' then
            L_SCON(7 downto 3) <= "00000";
        else
           if SFRW(10) = '1' then
               L_SCON(7 downto 3) <= RAMDI(7 downto 3);        
           end if;
        end if;
    end if;
end process setsconhi;
--*********************************************************************
setsconlo:process(NX1)
begin
    if NX1'event and NX1 ='1' then
        if CLEAR ='1' then
            LL_SCON(2 downto 0) <= "000";
        else
           if SFRW(10) = '1' then
               LL_SCON(2) <= RAMDI(2);
           elsif (RISET and SELRB8)= '1' then
               if DELRCV = '0' then
                  if L_SCON(7) ='0' then
                      if (L_SCON(6) and not L_SCON(5)) = '1' then
                          LL_SCON(2) <= MAJOUT;
                      end if;
                  else
                      LL_SCON(2) <= BITIN;
                  end if;
               else
                  LL_SCON(2) <= MAJOUT;
               end if;         
           end if;
           if TISET = '1' then
               LL_SCON(1) <= '1';
           elsif SFRW(10) = '1' then
               LL_SCON(1) <= RAMDI(1);         
           end if;
           if RISET = '1' then
               LL_SCON(0) <= '1';
           elsif SFRW(10) = '1' then
               LL_SCON(0) <= RAMDI(0);         
           end if;
        end if;
    end if;
end process setsconlo;
--*********************************************************************
gen1:process(RAMDI,L_SCON,LL_SCON,SFRW,CLEAR,RST16C,DIVTWO,PCON,NEWDATA,TSHIFT_EN)
begin
   DCKM <= ((RAMDI(7) xor L_SCON(7)) or (RAMDI(7) xor L_SCON(7))) and SFRW(10);
   MODE0 <= not(L_SCON(6) or L_SCON(7));
   CLEAR16C_RX <= CLEAR or RST16C;
   CLEAR16C_TX <= CLEAR or (TSHIFT_EN and NEWDATA);
   TCI(0) <= DIVTWO or PCON(7);
end process gen1;
--*********************************************************************
gen2:process(TX_EN,DIV2CK1,DATAEN,SOUT,MODE0,TSEND,RCV,SFRW,TXCLK,TXLASTBIT,TXEND)
begin
   TSHIFT_EN <= (TX_EN and (not DIV2CK1) and DATAEN) or SFRW(11);
   RXDO <= SOUT or (not MODE0) or (not TSEND); 
   TXDO <= not((MODE0 and (not TXCLK) and (RCV or TSEND)) or ((not MODE0) and TSEND and (not TXLASTBIT) and not(DATAEN and SOUT)));
   D0 <= not MODE0;
   TISET <= (MODE0 and TXEND) or (TXLASTBIT and not MODE0);
end process gen2;
--*********************************************************************
gen3:process(RSTQ1,RCV,RX_DIN,L_SCON,MODE0)
begin
   RST16C <= (not RSTQ1) and (RCV or  not RX_DIN) and L_SCON(4) and not MODE0;
end process gen3;
--*********************************************************************
set_riti:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR = '1' then
           LRITI <= '0';
       elsif MODE0 = '1' then
           LRITI <= LL_SCON(0) or LL_SCON(1);
       elsif (S_EN and DIV2CK1) = '1' then
           LRITI <= RISET or TISET or  LL_SCON(0) or LL_SCON(1);
       elsif (LL_SCON(0) or LL_SCON(1)) = '0' then
           LRITI <= '0';
       end if;
   end if;
end process set_riti;
--*********************************************************************
setdelrst:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if COUNT_EN = '1' then
         DELRST16C <= RST16C;
      end if;
   end if;
end process setdelrst;
--*********************************************************************
gen4:process(RCV,DELRCV,SWREC,RX_EN,DELRST16C,Q8,DIV2CK1,CLEAR,LORCV,CLR_RCV,L_SCON,END_DATA)
begin
   RSHIFT_EN <=  ((DELRCV or not SWREC) and RX_EN and (not DIV2CK1)and ((not CLR_RCV) or not L_SCON(7))) 
                 or (DELRST16C and LORCV) or CLEAR;
   RISET <= (Q8 and DELRCV and (not RCV) and not L_SCON(7)) or (L_SCON(7) and END_DATA);
end process gen4;
--*********************************************************************
gen5:process(FSREJ,RCV,MODE0,MAJOUT,CLEAR)
begin
   FLST <= CLEAR or (MAJOUT and RCV and (not MODE0) and not FSREJ);
end process gen5;
--*********************************************************************
misc1:process(RX_DIV,CLEAR16C_RX,MAJOUT,L_SCON,LL_SCON)
begin
   AF <=  RX_DIV(3) or (not RX_DIV(2)) or RX_DIV(1) or RX_DIV(0) or CLEAR16C_RX;
   AE <= RX_DIV(3) or (not RX_DIV(2)) or RX_DIV(1) or (not RX_DIV(0)) or CLEAR16C_RX;
   AH <= RX_DIV(3) or (not RX_DIV(2)) or (not RX_DIV(1)) or RX_DIV(0) or CLEAR16C_RX;
   AG <= ((not MAJOUT) and L_SCON(5)) or LL_SCON(0); 
end process misc1;
--*********************************************************************
countrxtx:process(L_SCON,CKMASK,DIV2CK1,LOV1)
begin
   COUNT_EN <= ((L_SCON(6) and (not CKMASK) and LOV1) or
                ((not L_SCON(6)) and (not CKMASK))) and not DIV2CK1;
end process countrxtx;
--*********************************************************************
setdelcnt:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if DIV2CK1 = '0' then
         DELCNT <= COUNT_EN;
      end if;
   end if;
end process setdelcnt;
--*********************************************************************
setckmask:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if SFRW(10) = '0' then
          CKMASK <= DCKM;
      end if;
    end if;
end process setckmask;
--*********************************************************************
gentxclk:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (T_EN and not DIV2CK1) = '1' then
          TXCLK <= '0';
      elsif SETTXCLK = '1' then
          TXCLK <= '1';
      end if;
   end if;
end process gentxclk;
--*********************************************************************
delayten:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (T_EN and DIV2CK1) = '1' then
         SETTXCLK <= '1';
      else
         SETTXCLK <= '0';
      end if;
   end if;
end process delayten;
--*********************************************************************
clksenab:process(MODE0,Q1,CKMASK,STATE12,RXC9,DELCNT)
begin
   case MODE0 is
       when '0' => TX_EN <= Q1 and DELCNT and not CKMASK;
                   RX_EN <= RXC9 and not CKMASK;
       when '1' => TX_EN <= (not CKMASK) and STATE12;
                   RX_EN <= (not CKMASK) and STATE12;
       when others => RX_EN <= 'X';
                      TX_EN <= 'X';
    end case;
end process clksenab;   
--*********************************************************************
divby2:process(NX1)
begin
   if NX1'event and NX1 ='1' then
        if CLEAR ='1' then
            DIVTWO <= '0';
        elsif COUNT_EN = '1' then
            DIVTWO <= not DIVTWO;
        end if;
    end if;
end process divby2;
--*********************************************************************
setrxc78:process(NX1)
begin
   if NX1'event and NX1 ='1' then 
       if DIV2CK1 = '0' then
           RXC7 <= (not AF) and COUNT_EN and TCI(0);
           RXC8 <= (not AE) and COUNT_EN and TCI(0);
           RXC9 <= (not AH) and COUNT_EN and TCI(0);
       end if;
   end if;
end process setrxc78;
--*********************************************************************
txprestoplat:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if ((T_EN and (not DIV2CK1)) = '1') then
          Q3 <= TXSTOPBIT;
          NEWDATA <= not DATAEN;
       end if;
   end if;
end process txprestoplat;
--*********************************************************************
txstopbitlat:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR ='1' then
          TSHIFT_IN <= '0';
       elsif (TSHIFT_EN = '1') then
           if NEWDATA = '0' then
              TSHIFT_IN <= Q3;
           else
              TSHIFT_IN <= L_SCON(3) or not L_SCON(7);
           end if;
       end if;
    end if;
end process; 
--*********************************************************************
setq1:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if COUNT_EN ='1' then
           Q1 <= TCI(0) and TX_DIV(3) and TX_DIV(2) and TX_DIV(0) and not TX_DIV(1);
       end if;
   end if;
end process setq1;
--*********************************************************************
setq5:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR ='1' then
           Q5 <= '0';
       elsif TISET ='1' then
           Q5 <= '0';
       elsif SFRW(11) ='1' then
           Q5 <= '1';
       end if;
    end if;
end process setq5;
--*********************************************************************
setq6:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (T_EN and DIV2CK1) ='0' then
          Q6 <= not Q5;
      end if;
   end if;
end process setq6;
--*********************************************************************
setq8:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if CLEAR = '1' then
          Q8 <= '0';
      elsif (RX_EN and  not DIV2CK1) ='1' then
          Q8 <= RCV and CLR_RCV and (MODE0 or not AG);
      end if;
   end if;
end process setq8;
--*********************************************************************

setselabb:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if CLEAR = '1' then
          SELRB8 <= '0';
      elsif (RX_EN and not DIV2CK1)='1' then
          SELRB8 <= (not AG) and  (not MODE0) and RCV and (not FRM(0));
      end if;
   end if;
end process setselabb;
--*********************************************************************
settsend:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if CLEAR = '1' then
          TSEND <= '0';
      elsif (((T_EN and (not Q5) and not DIV2CK1) or Q6) = '1') then
          TSEND <= '0';
      elsif (TX_EN and not DIV2CK1)= '1' then
          TSEND <= '1';
      end if;
   end if;
end process settsend;      
--*********************************************************************
setdataen:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (((T_EN and (not Q5) and not DIV2CK1) or Q6) = '1') then
          DATAEN <= '0';
      elsif (TX_EN and not DIV2CK1) ='1' then
          if (DATAEN or MODE0) = '0' then
             DATAEN <= TSEND;
          else 
             DATAEN <= '1'; 
          end if;
      end if;
    end if;
end process setdataen;
--*********************************************************************
settstopbit:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (TX_EN and not DIV2CK1)='1' then
         TXSTOPBIT <=  L_SCON(7) and (not DATAEN) and not Q6;
      end if;
   end if;
end process settstopbit;
--*********************************************************************
setlastbit:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (Q6 or CLEAR) = '1' then
          TXLASTBIT <= '0';         
      elsif ((TX_EN and DIV2CK1) = '1') then
          TXLASTBIT <= TSEND and  QLOW and (not TSHIFT_IN) and (not TXSTOPBIT);
      end if;
   end if;
end process setlastbit;       
--*********************************************************************
settxend:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (CLEAR or Q6)= '1' then
          TXEND <= '0';         
      elsif ((TX_EN and DIV2CK1) = '1') then
          TXEND <= TXLASTBIT;
      end if;
   end if;
end process settxend;       
--*********************************************************************
setrstqs:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR ='1' then
           RSTQ1 <= '0';
       elsif COUNT_EN= '1' then
           if TCI(0) = '1' then
              RSTQ1 <= RCV or not RX_DIN;
           end if;
       end if;
    end if;
end process setrstqs;
--*********************************************************************
setrcv:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR = '1' then
          RCV <= '0';
       elsif RST16C ='1' then
          RCV <= '1';
       elsif (RX_EN and not DIV2CK1)='1' then
          RCV <= (RCV and (not(FLST or (RCV and CLR_RCV)))) or not SWREC;
       end if;
    end if;
end process setrcv;
--*********************************************************************
--setrcv:process(NX1)
--begin
--   if NX1'event and NX1 ='1' then
--       if CLEAR = '1' then
--          RCV <= '0';
--       elsif RST16C ='1' then
--          RCV <= '1';
--       elsif (RX_EN and not DIV2CK1)='1' then
--          RCV <= (RCV and (not(RCV and CLR_RCV))) or not SWREC;
--       elsif (RX_EN and DIV2CK1)='1' then
--          RCV <= RCV and not FLST;
--       end if;
--    end if;
--end process setrcv;
--*********************************************************************
delbitclearrcv:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if CLEAR = '1' then
          DELCLRRCV <= '0';
       elsif RSHIFT_EN ='1' then
          DELCLRRCV <= not FRM(0);
       end if;
    end if;
end process delbitclearrcv;
--*********************************************************************
muxclrrcv:process(DELCLRRCV,FRM,L_SCON)
begin
    if L_SCON(7) = '0' then
       CLR_RCV <= not FRM(0);
    else
       CLR_RCV <= DELCLRRCV;
    end if;
end process muxclrrcv;
--*********************************************************************
setdelrcv:process(NX1)
begin
   if NX1'event and NX1 ='1' then
       if (T_EN ='1' and DIV2CK1 ='0') then
          DELRCV <= RCV;
       end if;
   end if;
end process setdelrcv;
--*********************************************************************
setswrec:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (T_EN and not DIV2CK1) = '1' then
         SWREC <= RCV or LL_SCON(0) or (not L_SCON(4)) or (not MODE0);
      end if;
   end if;
end process setswrec;
--*********************************************************************
setmajq1:process(NX1) 
begin
   if NX1'event and NX1 ='1' then
--      if (S_EN and not DIV2CK1) = '1' then
      if RXC7 = '1' then
          MAJQ1 <= RX_DIN;
      end if;
    end if;
end process setmajq1;
--*********************************************************************
setmajq2:process(NX1) 
begin
   if NX1'event and NX1 ='1' then
      if RXC8 = '1' then
          MAJQ2 <= RX_DIN;
      end if;
    end if;
end process setmajq2;
--*********************************************************************
sample:process(NX1)-- 9th bit latch
begin
   if NX1'event and NX1 ='1' then
           RX_DIN <= DI(0);
   end if;
end process sample;
--*********************************************************************
majin:process(RX_DIN,MAJQ2,MAJQ1)
begin
   MAJOUT <= (MAJQ1 and RX_DIN) or (MAJQ1 and MAJQ2) or (MAJQ2 and RX_DIN);
end process majin;
--*********************************************************************
setbitin:process(NX1)-- 9th bit latch
begin
   if NX1'event and NX1 ='1' then
       if (RSHIFT_EN = '1' and DIV2CK1 ='0') then
          if LORCV = '0' then
             BITIN <= MAJOUT;
          else 
             BITIN <= '1';
          end if;
       end if;
    end if;
end process setbitin;
--*********************************************************************
m0in:process(NX1)
begin
   if NX1'event and NX1 = '1' then
       if (S_EN = '1' and DIV2CK1 = '0') then
          MODE0_IN <= RX_DIN;
       end if;
   end if; 
end process m0in;
--*********************************************************************
muxrshiftin:process(MODE0,MODE0_IN,BITIN)
begin
   if MODE0 = '0' then
       RSHIFT_IN <= BITIN;
   else
       RSHIFT_IN <= MODE0_IN;
   end if;
end process muxrshiftin;
--*********************************************************************
setfsrej:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if RCV = '0' then
          FSREJ <= '0';
      elsif (RX_EN = '1' and DIV2CK1 ='0') then
          FSREJ <= DELRCV;
      end if;
   end if;
end process setfsrej;
--*********************************************************************
setsbuf:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if CLEAR = '1' then
          SBUF <= "00000000";
      elsif (RISET and DIV2CK1) ='1' then
          SBUF <= FRM;
      end if;
   end if;
end process setsbuf;
--*********************************************************************
setldrcv:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (RST16C or CLEAR)= '1' then
          LORCV <= '1';
      elsif (RX_EN = '0' and DIV2CK1 ='0') then
          LORCV <= not RCV;
      end if;
   end if;
end process setldrcv;
--*********************************************************************
set_end_data:process(NX1)
begin
   if NX1'event and NX1 ='1' then
        if (CLEAR or END_DATA or (RCV and not DELRCV)) = '1' then
             END_DATA <= '0';
        elsif (RSHIFT_EN and (not FRM(0)) and not DIV2CK1) = '1' then
             END_DATA <= '1';
        end if;
   end if;
end process set_end_data;
--*********************************************************************
localout:process(LL_SCON,L_SCON,LTCI,LRCI,LRITI)
-- Rename divider carry outputs (LTCI & LRCI) for verilog compatibility.
begin
   SCON(7 downto 3) <= L_SCON;
   SCON(2 downto 0) <= LL_SCON;
   TCI(3 downto 1) <= LTCI;
   RCI(3 downto 1) <= LRCI;
   RITI <= LRITI;
end process localout;
--*********************************************************************

--*********************************************************************
end m3s028bo_rtl;
--*********************************************************************


