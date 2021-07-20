--Accumulator and ALU Temporary Register Number 2 for M8051
--(c) Copyright Mentor Graphics Corporation and Licensees 1997. All rights reserved
--v1.006
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s005bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       03th September 1995
--Purpose       :       Accumulator and temp2 latch sub block for m8051
--Version       :       1.006
--Mod Date      :       24th March 1997
--Mod History	:       1.006 Redundant declarations removed.
--                      1.005 parity tree corrected.
--                      1.004 ECN 878: Read-modify-write instructions 
--                            use c2s2p2 to load ALU temp register 2.
--                            All temp & Accumulator loads now take
--                            place at the end of phase 2.
--                      1.003- ACCO name changed to ACC0
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
entity m3s005bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ACCDAT,
            BREG:
            out std_logic_vector(7 downto 0);
            ACLDAT:
            out std_logic_vector(9 downto 0);
            PAR,
            ACC0,
            DAAL,
            DAAH:
            out std_logic;
            CYC:
            in std_logic_vector(1 downto 1);
            PSWDAT:
            in std_logic_vector(7 downto 6);
            STATD:
            in std_logic_vector(6 downto 2);-- note bit 4 not used
            ACCADD:
            in std_logic_vector(9 downto 0);        
            ALUDAT,
            CPRDDM,
            RDAT,
            IMMDAT,
            RAMDI:
            in std_logic_vector(7 downto 0);
            SFRW:
            in std_logic_vector(21 downto 20);
            DAA,
            LCYC,
            DIV2CK,
            CO,
            RST,
            NX1:
            in std_logic
            );       
end m3s005bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s005bo_rtl of m3s005bo_e is
--*********************************************************************
--*********************************************************************
--Signal definitions
--*********************************************************************
signal MULDIV,AD,AE,AF,AG,AH,AI,AJ:std_logic;
signal BD,BE,BF:std_logic;
signal ACC_EN, TEMP2_EN, B_REG_EN:std_logic;   -- register load controls
signal BIT0MOD,ADD2MOD,ADD3MOD:std_logic;
signal MUXVECT1,MUXVECT2,MUXVECT3:std_logic_vector(1 downto 0);
signal LDATAA,LDATAB,LDATAC,LDATAD:std_logic_vector(7 downto 0);
signal REGMOD,ALUMOD,L_ACCDAT:std_logic_vector(7 downto 0);
--*********************************************************************
begin
--*********************************************************************
--Process Definitions
--*********************************************************************
--*********************************************************************
--Bus assignments
--*********************************************************************
set_ldataa:process(ACCADD,ALUMOD,IMMDAT,REGMOD,LDATAB)
begin
     case ACCADD(1 downto 0) is
          when "00" =>  LDATAA <= ALUMOD;
          when "01" =>  LDATAA <= IMMDAT;
          when "10" =>  LDATAA <= REGMOD;
          when "11" =>  LDATAA <= LDATAB;
          when others => LDATAA <= "XXXXXXXX" ;
      end case;
end process set_ldataa;
--*********************************************************************
set_ldatab:process(ACCADD,L_ACCDAT,CO)
begin
  case ACCADD(2) is
    when '0' => LDATAB(6 downto 0) <= L_ACCDAT(7 downto 1);LDATAB(7) <= CO;
    when '1' => LDATAB(7 downto 1) <= L_ACCDAT(6 downto 0);LDATAB(0) <= CO;
    when others => LDATAB <= "XXXXXXXX";
  end case;
end process set_ldatab;
--*********************************************************************
setmuxvect1:process(ADD3MOD,ADD2MOD)
begin
  MUXVECT1 <= ADD3MOD&ADD2MOD;
end process setmuxvect1;
--*********************************************************************
set_ldatac:process(MUXVECT1,L_ACCDAT,RDAT,BIT0MOD,ALUDAT)
begin
     case MUXVECT1 is
          when "00" =>  LDATAC <= L_ACCDAT;
          when "01" =>  LDATAC(0) <=BIT0MOD;LDATAC(7 downto 1) <="0000000";
          when "10" =>  LDATAC <= RDAT;
          when "11" =>  LDATAC <= ALUDAT;
          when others => LDATAC <= "XXXXXXXX";
     end case;
end process set_ldatac;
--*********************************************************************
setmuxvect2:process(ACCADD,SFRW)
begin
  MUXVECT2 <= SFRW(20)&ACCADD(2);
end process setmuxvect2;
--*********************************************************************
set_ldatad:process(ALUDAT,CPRDDM,RAMDI,MUXVECT2)
begin
     case  MUXVECT2 is
          when "00" =>  LDATAD <= ALUDAT;
          when "01" =>  LDATAD <= CPRDDM;
          when "10" =>  LDATAD <= RAMDI;
          when "11" =>  LDATAD <= RAMDI;
          when others => LDATAD <= "XXXXXXXX";
     end case;
end process set_ldatad;
--*********************************************************************

--*********************************************************************
--General logic
--*********************************************************************
setmuxvect3:process(BD,BE)
begin
   MUXVECT3 <= BD&BE;
end process setmuxvect3;
--*********************************************************************
gencon1:process(MUXVECT3,L_ACCDAT,CO)
begin
     case  MUXVECT3 is
          when "00" => BIT0MOD <= '0';
          when "01" => BIT0MOD <= CO;
          when "10" => BIT0MOD <= L_ACCDAT(7);
          when "11" => BIT0MOD <= '1';
          when others => BIT0MOD <= 'X';
     end case; 
end process gencon1;
--*********************************************************************
gencon2:process(MULDIV,AD,AF,BF,ACCADD)
begin
    ADD3MOD <= ACCADD(3) and not BF;
    ADD2MOD <= MULDIV or AD or AF;
end process gencon2;
--*********************************************************************
gencon3:process(ACCADD,RDAT,L_ACCDAT)
begin
  case ACCADD(4) is
    when '0' => REGMOD(7 downto 4) <= RDAT(7 downto 4);
    when '1' => REGMOD(7 downto 4) <= L_ACCDAT(7 downto 4);
    when others => REGMOD(7 downto 4) <= "XXXX";
  end case;
end process gencon3;
--*********************************************************************
gencon4:process(SFRW,ALUDAT,RAMDI)
begin
  case SFRW(21) is
    when '0' => ALUMOD <= ALUDAT;
    when '1' => ALUMOD <= RAMDI;
    when others => ALUMOD <= "XXXXXXXX";
  end case;
end process gencon4;
--*********************************************************************
misc1:process(STATD,ACCADD,L_ACCDAT,PSWDAT,CYC)
begin
    MULDIV <= ACCADD(0) and ACCADD(1);
    AD <= STATD(2) and ACCADD(6);
    AE <= CYC(1) and STATD(2) and ACCADD(2);
    AF <= STATD(5) and ACCADD(5);
    AG <= STATD(2) and PSWDAT(6);
    AH <= STATD(5) and PSWDAT(7);
    AI <= (L_ACCDAT(1) or L_ACCDAT(2)) and L_ACCDAT(3) and STATD(2);
    AJ <= (L_ACCDAT(5) or L_ACCDAT(6)) and L_ACCDAT(7) and STATD(5);
end process misc1;
--*********************************************************************
misc2:process(MULDIV,AD,AE,AF,STATD,CYC)
begin
    BD <= AD or AE;
    BE <= AD or AF;
    BF <= STATD(2) and MULDIV and CYC(1);
end process misc2;
--*********************************************************************
load_reg_en:process(MULDIV, DAA, ACCADD, LCYC, SFRW, STATD, DIV2CK)
-- Enable accumulator load: This may happen at the end of s3p2, s6p2,
-- or alternatively at the end of s5p2 for exchange instructions.
-- The B register may only load at the end of s6p2.
begin
   ACC_EN <= not DIV2CK and (
             (STATD(3) and (MULDIV or DAA)) or
             (STATD(5) and ACCADD(8)) or
             (STATD(6) and (MULDIV or (ACCADD(7) and LCYC) or SFRW(21)))
             );
   B_REG_EN <= not DIV2CK and (
               (STATD(6) and LCYC and MULDIV) or SFRW(20)
               );
end process load_reg_en;
--*********************************************************************
load_temp_2_en: process(STATD, CYC, ACCADD, MULDIV, DIV2CK)
-- temporary register 2 loads on s2p2 and s5p2.  This happens always in
-- cycle 1 and in higher cycle numbers for selected instructions.
begin
   TEMP2_EN <= not DIV2CK and (
               (STATD(2) and (CYC(1) or ACCADD(5) or MULDIV or ACCADD(9)))
               or
               (STATD(5) and (CYC(1) or ACCADD(5) or MULDIV))
               );
end process load_temp_2_en;
--*********************************************************************

--*********************************************************************
--Register Assignments
--*********************************************************************
update_registers: process(RST,NX1)
-- Load the accumulator, B register and temporary register 2 (ACLDAT).
begin
   if RST ='1'then
      L_ACCDAT <= "00000000";
      BREG <= "00000000";
      ACLDAT(9 downto 0) <= "0000000000";
      ACC0 <= '0';
   elsif NX1'event and NX1='1' then
      if ACC_EN ='1' then L_ACCDAT <= LDATAA;
      end if;
      if B_REG_EN ='1' then BREG <= LDATAD;
      end if;
      if TEMP2_EN ='1' then
         ACLDAT(9) <= PSWDAT(7);
         ACLDAT(8) <= PSWDAT(6);
         ACLDAT(7 downto 0) <= LDATAC(7 downto 0);
         ACC0 <= L_ACCDAT(0);
      end if;
   end if;
end process update_registers;  
--*********************************************************************
--output assignments
--*********************************************************************
genout:process(AG,AH,AI,AJ,L_ACCDAT,RDAT)
begin
   ACCDAT <= L_ACCDAT;
   REGMOD(3 downto 0) <= RDAT(3 downto 0);
   DAAL <= AG or AI;
   DAAH <= AH or AJ;
   PAR <= L_ACCDAT(0) xor L_ACCDAT(1) xor L_ACCDAT(2) xor L_ACCDAT(3)
        xor L_ACCDAT(4) xor L_ACCDAT(5) xor L_ACCDAT(6) xor L_ACCDAT(7);
end process genout;
--*********************************************************************
end m3s005bo_rtl;
--*********************************************************************
