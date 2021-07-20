-- 8-Bit Arithmetic Logic Unit for m8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights Reserved.
--v1.005
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s003bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       14th October 1995
--Purpose       :       2 x 4 bit ALU,with look ahead carry for m8051
--Version       :       1.005
--Mod Date      :       3rd April 1997
--Mod History	:       1.005 Look-ahead carry restored to design.
--                      1.004 Sensitivity list revisions, redundant
--                            decode removed.
--                      1.003-ECN 857-CARI in sensitivity list
--                      1.002-Calling file name changed to m8051.vhd
--                      1.001(Original)
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--Calls to              :m3s002bo.vhd
--                      :
--                      :
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;
use WORK.all;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s003bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ALUDAT,
            CPRDDM:
            out std_logic_vector(7 downto 0);
            CO,
            ACO,
            OV,
            BBIT:
            out std_logic;
            ACLDAT:
            in std_logic_vector(9 downto 0);         
            TMPDAT:
            in std_logic_vector(7 downto 0);
            ALUC:
            in std_logic_vector(17 downto 0);--bit 13 not used
            ACCDAT:
            in std_logic_vector(7 downto 7);
            BIT_POSN:
            in std_logic_vector(2 downto 0);
            NMULAB,
            NDIVAB,
            DAA,
            ACC0:
            in std_logic
            );       
end m3s003bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s003bo_rtl of m3s003bo_e is
--*********************************************************************
--*********************************************************************
--Component Definitions
--*********************************************************************
-- ALU primitive components: bit slice and 4-bit carry look-ahead units

component m3s002bo_e
       port(P,
            CO:   out std_logic;
            ALUC: in  std_logic_vector(5 downto 0);
            A,
            B:    in std_logic 
            ); 
end component;

component m3s041bo_e
       port(S:    out std_logic_vector(3 downto 0);
            P:    in  std_logic_vector(3 downto 0);
            G:    in  std_logic_vector(2 downto 0);
            C_IN: in  std_logic;
            C_EN: in  std_logic 
            );
end component;

--*********************************************************************
--Signal definitions
--*********************************************************************
signal QCI,CMUX,CBEN,CAM,CARI,LBBIT:std_logic;
signal AA,AB,AC,AD,AE,AF,PROP_LO,AH,AR,AS,AT,AU,AV,AW:std_logic;
signal AAA,AAB,AAC,AAD,AAE,AAF:std_logic;
signal GEN_LO,BB,BC,BD,BE,BF,BG,CA,CB,CC,CD,CE,CF,CG,CH,DA,DB,DC:std_logic;
signal EJ, EK: std_logic;
signal LOCALA,LOCALB,LOCALC,LOCALD,LOCALE,LOCALF:std_logic;
signal ALU_PROP, ALU_GEN, ALU_SUM: std_logic_vector(7 downto 0);
signal ALUP, LDATAA: std_logic_vector(7 downto 0);
signal muxvect1:std_logic_vector(1 downto 0);
--*********************************************************************
--Port Mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s002bo_e
 port map(
          P => ALU_PROP(0),
          CO => ALU_GEN(0),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(0),
          B => TMPDAT(0)
         );
--*********************************************************************
U2:m3s002bo_e
 port map(
          P => ALU_PROP(1),
          CO => ALU_GEN(1),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(1),
          B => TMPDAT(1)
         );
--*********************************************************************
U3:m3s002bo_e
 port map(
          P => ALU_PROP(2),
          CO => ALU_GEN(2),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(2),
          B => TMPDAT(2)
         );
--*********************************************************************
U4:m3s002bo_e
 port map(
          P => ALU_PROP(3),
          CO => ALU_GEN(3),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(3),
          B => TMPDAT(3)
         );
--*********************************************************************
U5:m3s002bo_e
 port map(
          P => ALU_PROP(4),
          CO => ALU_GEN(4),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(4),
          B => TMPDAT(4)
         );
--*********************************************************************
U6:m3s002bo_e
 port map(
          P => ALU_PROP(5),
          CO => ALU_GEN(5),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(5),
          B => TMPDAT(5)
         );
--*********************************************************************
U7:m3s002bo_e
 port map(
          P => ALU_PROP(6),
          CO => ALU_GEN(6),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(6),
          B => TMPDAT(6)
         );
--*********************************************************************
U8:m3s002bo_e
 port map(
          P => ALU_PROP(7),
          CO => ALU_GEN(7),
          ALUC => ALUC(5 downto 0),
          A => ACLDAT(7),
          B => TMPDAT(7)
         );
--*********************************************************************
U9:m3s041bo_e
 port map( 
          S => ALU_SUM(3 downto 0),
          P => ALU_PROP(3 downto 0),
          G => ALU_GEN(2 downto 0),
          C_IN => QCI,
          C_EN => CBEN
         );
--*********************************************************************
U10:m3s041bo_e
 port map( 
          S => ALU_SUM(7 downto 4),
          P => ALU_PROP(7 downto 4),
          G => ALU_GEN(6 downto 4),
          C_IN => DA,
          C_EN => CBEN
         );
--*********************************************************************
--Process Definiions
--*********************************************************************
general1:process(ALUC,ACC0,DB,AV,NMULAB,NDIVAB)
begin
   CMUX <= (NMULAB or ACC0) and (( DB xor AV) or NDIVAB);
   CBEN <= ALUC(4) or ALUC(5);
   CARI  <= DB xor AV;
end process general1;
--*********************************************************************
general2:process(CARI,CMUX,AAF,ALUC)
begin
   CAM <= CARI and CMUX;
   QCI <= not (ALUC(5) xor not AAF);
end process general2;
--*********************************************************************
misc1:process(ALU_PROP,ALU_GEN,QCI,CBEN,LBBIT,ALUC,ACLDAT,NDIVAB)
begin
   AA <= ALU_GEN(0) and ALU_PROP(1) and ALU_PROP(2) and ALU_PROP(3);
   AB <= ALU_GEN(1) and ALU_PROP(2) and ALU_PROP(3);
   AC <= ALU_GEN(2) and ALU_PROP(3);
   AD <= ALU_GEN(4) and ALU_PROP(5) and ALU_PROP(6) and ALU_PROP(7);
   AE <= ALU_GEN(5) and ALU_PROP(6) and ALU_PROP(7);
   AF <= ALU_GEN(6) and ALU_PROP(7);
   PROP_LO <= ALU_PROP(0) and ALU_PROP(1) and ALU_PROP(2) and ALU_PROP(3);
   AH <= ALU_PROP(4) and ALU_PROP(5) and ALU_PROP(6) and ALU_PROP(7);  
   AR <= (not ACLDAT(9)) and (not LBBIT) and ALUC(9);
   AS <= (not ACLDAT(9)) and LBBIT and ALUC(10);
   AT <= ACLDAT(9) and LBBIT and ALUC(11);
   AU <= ACLDAT(9) and (not LBBIT) and ALUC(12);
   AV <= ALUC(5) and NDIVAB;
   AW <= ALUC(7) and ALUC(15);
end process misc1;
--*********************************************************************
misc2:process(AA,AB,AC,AD,AE,AF,AR,AS,AT,AU,AW,AAA,AAB,AAD,AAE,ALU_GEN,ALUC,NMULAB,NDIVAB)
begin
   GEN_LO <= AA or AB or AC or ALU_GEN(3);
   BB <= AD or AE or AF or ALU_GEN(7);
   BC <= AR or AS or AT or AU;
   BD <= AW or not ALUC(14);
   BE <= AAA or AAB or ALU_GEN(6);
   BF <= AAD and not NMULAB;
   BG <= AAE or NDIVAB;
end process misc2;
--*********************************************************************
misc3:process(PROP_LO,AH,GEN_LO,BB,BE,BF,BG,AAC,QCI)
begin
   CA <= (QCI or GEN_LO) and (GEN_LO or PROP_LO);
   CB <= QCI or GEN_LO or BB;
   CC <= PROP_LO or GEN_LO or BB; 
   CD <= BB or AH;
   CE <= QCI or GEN_LO or BE;
   CF <= PROP_LO or GEN_LO or BE;
   CG <= AAC or BE;
   CH <= BF or not BG;
end process misc3;
--*********************************************************************
misc4:process(CA,CB,CC,CD,CE,CF,CG,CBEN)
begin
   DA <= CA and CBEN;
   DB <= CB and CC and CD;
   DC <= CE and CF and CG;
end process misc4;
--*********************************************************************
misc5:process(DC, CARI, LOCALF, DAA, ALUC)
begin
   EJ <= LOCALF or (DAA and CARI);
   EK <= (DC xor ALUC(5)) xor CARI;
end process misc5;
--*********************************************************************
misc6:process(ALU_GEN,ALU_PROP,ALUP,TMPDAT,ACLDAT,ALUC,CBEN)
begin
   AAA <= ALU_GEN(4) and ALU_PROP(5) and ALU_PROP(6);
   AAB <= ALU_GEN(5) and ALU_PROP(6);
   AAC <= ALU_PROP(4) and ALU_PROP(5) and ALU_PROP(6);
   AAD <= ALUP(0) or ALUP(1) or ALUP(2) or ALUP(3) or ALUP(4) or
          ALUP(5) or ALUP(6) or ALUP(7);
   AAE <= TMPDAT(0) or TMPDAT(1) or TMPDAT(2) or TMPDAT(3) or TMPDAT(4) or
          TMPDAT(5) or TMPDAT(6) or TMPDAT(7); 
   AAF <= ACLDAT(9) and ALUC(13) and CBEN;
end process misc6;
--*********************************************************************
set_dataa:process(ALU_SUM,ACLDAT,CMUX)
begin
   case CMUX is
       when '0' => LDATAA <= ACLDAT(7 downto 0);
       when '1' => LDATAA <= ALU_SUM;
       when others => LDATAA <= "XXXXXXXX";
   end case;
end process set_dataa;
--*********************************************************************
set_loca:process(ACCDAT,ACLDAT,NDIVAB)
begin
   case NDIVAB is
       when '0' => LOCALA <= ACCDAT(7);
       when '1' => LOCALA <= ACLDAT(7);
       when others => LOCALA <= 'X';
   end case;
end process set_loca;
--*********************************************************************
set_locb:process(CAM,ACLDAT,NMULAB)
begin
   case NMULAB is
       when '0' => LOCALB <= CAM;
       when '1' => LOCALB <= ACLDAT(9);
       when others => LOCALB <= 'X';
   end case;
end process set_locb;
--*********************************************************************
set_locc:process(LOCALA,LDATAA,ACLDAT,LOCALB,ALUC)
begin
   case ALUC(15) is
       when '0' => LOCALC <= LOCALA;LOCALD <= LDATAA(0);
       when '1' => LOCALC <= ACLDAT(9);LOCALD <= LOCALB;
       when others => LOCALC <= 'X';LOCALD <= 'X';
   end case;
end process set_locc;
--*********************************************************************
set_loce:process(CA,ACLDAT,ALUC)
begin
   case ALUC(8) is
       when '0' => LOCALE <= ACLDAT(8);
       when '1' => LOCALE <= CA;
       when others => LOCALE <= 'X';
   end case;
end process set_loce;
--*********************************************************************
set_locf:process(BC,ACLDAT,ALUC)
begin
   case ALUC(16) is
       when '0' => LOCALF <= BC;
       when '1' => LOCALF <= ACLDAT(9);
       when others => LOCALF <= 'X';
   end case;
end process set_locf;
--*********************************************************************
set_alup:process(LDATAA,LOCALC,LOCALD,ALUC)
begin
   case ALUC(7 downto 6) is
       when "00" => ALUP <= LDATAA;
       when "01" => ALUP(6 downto 0) <= LDATAA(7 downto 1);ALUP(7) <= LOCALD;
       when "10" => ALUP(0) <= LOCALC;ALUP(7 downto 1) <= LDATAA(6 downto 0);
       when "11" => ALUP(3 downto 0) <= LDATAA(7 downto 4);
                    ALUP(7 downto 4) <= LDATAA(3 downto 0);
       when others => ALUP <= "XXXXXXXX";
   end case;
end process set_alup;
--*********************************************************************
setmuxvect:process(ALUC,BD)
begin
   MUXVECT1(1 downto 0) <= ALUC(15)&BD;
end process setmuxvect; 
--*********************************************************************
set_coout:process(LDATAA,CARI,EJ,MUXVECT1)
begin
   case MUXVECT1(1 downto 0) is
       when "00" => CO <= EJ;
       when "01" => CO <= CARI;
       when "10" => CO <= LDATAA(0);
       when "11" => CO <= LDATAA(7);
       when others => CO <= 'X';
   end case;
end process set_coout;
--*********************************************************************
set_bbit:process(ACLDAT,BIT_POSN)
begin
   case BIT_POSN(2 downto 0) is
     when "000" => LBBIT <= ACLDAT(0);
     when "001" => LBBIT <= ACLDAT(1);
     when "010" => LBBIT <= ACLDAT(2);
     when "011" => LBBIT <= ACLDAT(3);
     when "100" => LBBIT <= ACLDAT(4);
     when "101" => LBBIT <= ACLDAT(5);
     when "110" => LBBIT <= ACLDAT(6);
     when "111" => LBBIT <= ACLDAT(7);
     when others => LBBIT <= 'X';
   end case;
end process set_bbit;
--*********************************************************************
set_aludat:process(BC,BIT_POSN,ALUP,ALUC)
begin
   if ALUC(17) = '1' then
      ALUDAT <= ALUP;
   else
      case BIT_POSN(2 downto 0) is
      when "000" => ALUDAT(0) <= BC;ALUDAT(7 downto 1) <=ALUP(7 downto 1);
      when "001" => ALUDAT(0) <= ALUP(0);ALUDAT(1) <= BC; 
                    ALUDAT(7 downto 2) <= ALUP(7 downto 2);
      when "010" => ALUDAT(1 downto 0) <=ALUP(1 downto 0);
                    ALUDAT(2) <= BC; ALUDAT(7 downto 3) <= ALUP(7 downto 3);
      when "011" => ALUDAT(2 downto 0) <=ALUP(2 downto 0);
                    ALUDAT(3) <= BC; ALUDAT(7 downto 4) <= ALUP(7 downto 4);
      when "100" => ALUDAT(3 downto 0) <=ALUP(3 downto 0);
                    ALUDAT(4) <= BC; ALUDAT(7 downto 5) <= ALUP(7 downto 5);
      when "101" => ALUDAT(4 downto 0) <=ALUP(4 downto 0);
                    ALUDAT(5) <= BC; ALUDAT(7 downto 6) <= ALUP(7 downto 6);
      when "110" => ALUDAT(5 downto 0) <=ALUP(5 downto 0);
                    ALUDAT(6) <= BC; ALUDAT(7) <= ALUP(7);
      when "111" => ALUDAT(6 downto 0) <=ALUP(6 downto 0);
                    ALUDAT(7) <= BC;
      when others => ALUDAT <= "XXXXXXXX";
      end case;
   end if;
end process set_aludat;
--*********************************************************************
genout:process(CH,EK,LDATAA,LOCALE,ALUC,LBBIT,NMULAB,NDIVAB)
begin
   ACO <= LOCALE xor ALUC(5);   
   CPRDDM <= LDATAA;
   OV <= (EK and NMULAB and NDIVAB) or CH;
   BBIT <= LBBIT;
end process genout;
--*********************************************************************
end m3s003bo_rtl;
--*********************************************************************
