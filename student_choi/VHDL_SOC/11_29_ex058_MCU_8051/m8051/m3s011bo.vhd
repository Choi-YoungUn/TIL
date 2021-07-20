--Program Counter Increment and Relative Offset Generator for M8051
--(c) Copyright Mentor Graphics corporation and Licensors 1997. All rights reserved
--v1.004
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s011bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       23th September 1995
--Purpose       :       Program counter inc and relative offset gen for m8051
--Version       :       1.004
--Mod Date      :       6th February 1997
--Mod History	:       1.004 Name changes only
--                      1.003 ECN 878: Names changed for legibility
--                      1.002-added LNGC,LNPC buses to allow verilog conversion,
--                            no circuit change.
--                      1.001(Original)
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s010bo.vhd
--Calls to              :m3s027bo.vhd
--                      :m3s040bo.vhd
--                      :
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s011bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(NEXT_REL_PC:
            out std_logic_vector(15 downto 0);
            PROGRAM_COUNT:
            in std_logic_vector(15 downto 0);
            IMMDAT:
            in std_logic_vector(7 downto 0);
            PC_INCR,
            JMP_REL:
            in std_logic
            );       
end m3s011bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s011bo_rtl of m3s011bo_e is
--*********************************************************************
--*********************************************************************
--Component Definitions
--*********************************************************************
--Decode matrix
component m3s027bo_e
       port(SUM:
            out std_logic_vector(3 downto 0);
            NG,
            P:
            in std_logic_vector(3 downto 0);
            NCI:
            in std_logic 
            ); 
end component;
--*********************************************************************
component m3s040bo_e
       port(NGC,
            NPC:
            out std_logic;
            NG,
            P:
            in std_logic_vector(3 downto 0) 
            );       
end component;
--*********************************************************************
--Signal definitions
--*********************************************************************
signal NCI:std_logic;
signal AA,AB,AC,AD,AE,AF,AG,AH,AI:std_logic;
signal LBUSA:std_logic_vector(7 downto 0);
signal NG,P:std_logic_vector(15 downto 0);
signal LNGC,LNPC:std_logic_vector(1 downto 0);
signal NGC,NPC,NC:std_logic_vector(2 downto 0);
--*********************************************************************
--Port Mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s027bo_e
 port map(
          SUM => NEXT_REL_PC(15 downto 12),
          NG => NG(15 downto 12), 
          P => P(15 downto 12),
          NCI => NC(2) 
         );
--*********************************************************************
U2:m3s027bo_e
 port map(
          SUM => NEXT_REL_PC(11 downto 8),
          NG => NG(11 downto 8), 
          P => P(11 downto 8),
          NCI => NC(1) 
         );
--*********************************************************************
U3:m3s027bo_e
 port map(
          SUM => NEXT_REL_PC(7 downto 4),
          NG => NG(7 downto 4), 
          P => P(7 downto 4),
          NCI => NC(0) 
         );
--*********************************************************************
U4:m3s027bo_e
 port map(
          SUM => NEXT_REL_PC(3 downto 0),
          NG => NG(3 downto 0), 
          P => P(3 downto 0),
          NCI => NCI 
         );
--*********************************************************************
U5:m3s040bo_e
 port map(
          NGC => LNGC(1),
          NPC => LNPC(1),
          NG => NG(7 downto 4),
          P => P(7 downto 4)
         );
--*********************************************************************
U6:m3s040bo_e
 port map(
          NGC => LNGC(0),
          NPC => LNPC(0),
          NG => NG(3 downto 0),
          P => P(3 downto 0)
         );
--*********************************************************************

--*********************************************************************
--Process Definiions
--*********************************************************************
setabus:process(IMMDAT,JMP_REL)
begin
   LBUSA(0) <= JMP_REL and IMMDAT(0); 
   LBUSA(1) <= JMP_REL and IMMDAT(1);
   LBUSA(2) <= JMP_REL and IMMDAT(2); 
   LBUSA(3) <= JMP_REL and IMMDAT(3); 
   LBUSA(4) <= JMP_REL and IMMDAT(4); 
   LBUSA(5) <= JMP_REL and IMMDAT(5); 
   LBUSA(6) <= JMP_REL and IMMDAT(6); 
   LBUSA(7) <= JMP_REL and IMMDAT(7);  
end process setabus;
--*********************************************************************
set_ng:process(LBUSA,PROGRAM_COUNT)
begin
   NG(0) <= not(PROGRAM_COUNT(0) and LBUSA(0));
   NG(1) <= not(PROGRAM_COUNT(1) and LBUSA(1));
   NG(2) <= not(PROGRAM_COUNT(2) and LBUSA(2));
   NG(3) <= not(PROGRAM_COUNT(3) and LBUSA(3));
   NG(4) <= not(PROGRAM_COUNT(4) and LBUSA(4));
   NG(5) <= not(PROGRAM_COUNT(5) and LBUSA(5));
   NG(6) <= not(PROGRAM_COUNT(6) and LBUSA(6));
   NG(7) <= not(PROGRAM_COUNT(7) and LBUSA(7));
   NG(8) <= not(PROGRAM_COUNT(8) and LBUSA(7));
   NG(9) <= not(PROGRAM_COUNT(9) and LBUSA(7));
   NG(10) <= not(PROGRAM_COUNT(10) and LBUSA(7));
   NG(11) <= not(PROGRAM_COUNT(11) and LBUSA(7));
   NG(12) <= not(PROGRAM_COUNT(12) and LBUSA(7));
   NG(13) <= not(PROGRAM_COUNT(13) and LBUSA(7));
   NG(14) <= not(PROGRAM_COUNT(14) and LBUSA(7));
   NG(15) <= not(PROGRAM_COUNT(15) and LBUSA(7));
end process set_ng;
--*********************************************************************
set_p:process(LBUSA,PROGRAM_COUNT)
begin
    P(0) <= PROGRAM_COUNT(0) or LBUSA(0);
    P(1) <= PROGRAM_COUNT(1) or LBUSA(1);
    P(2) <= PROGRAM_COUNT(2) or LBUSA(2);
    P(3) <= PROGRAM_COUNT(3) or LBUSA(3);
    P(4) <= PROGRAM_COUNT(4) or LBUSA(4);
    P(5) <= PROGRAM_COUNT(5) or LBUSA(5);
    P(6) <= PROGRAM_COUNT(6) or LBUSA(6);
    P(7) <= PROGRAM_COUNT(7) or LBUSA(7);
    P(8) <= PROGRAM_COUNT(8) or LBUSA(7);
    P(9) <= PROGRAM_COUNT(9) or LBUSA(7);
    P(10) <= PROGRAM_COUNT(10) or LBUSA(7);
    P(11) <= PROGRAM_COUNT(11) or LBUSA(7);
    P(12) <= PROGRAM_COUNT(12) or LBUSA(7);
    P(13) <= PROGRAM_COUNT(13) or LBUSA(7);
    P(14) <= PROGRAM_COUNT(14) or LBUSA(7);
    P(15) <= PROGRAM_COUNT(15) or LBUSA(7);
end process set_p;
--*********************************************************************
set_nc:process(AA,AB,AC,AD,AE,AF,AG,AH,AI)
begin
    NC(0) <= AH or AI;
    NC(1) <= AE or AF or AG;
    NC(2) <= AA or AB or AC or AD;
end process set_nc;
--*********************************************************************
misc1:process(PC_INCR,NG,P)
begin
    NCI <= not PC_INCR;
    NGC(2) <= NG(8) and NG(9) and NG(10) and NG(11);
    NPC(2) <= not(P(8) and P(9) and P(10) and P(11)); 
end process misc1;
--*********************************************************************
misc2:process(NGC,NPC,NCI)
begin
    AA <= NGC(2) and NPC(2);
    AB <= NGC(2) and NGC(1) and NPC(1);
    AC <= NGC(2) and NGC(1) and NGC(0) and NPC(0);
    AD <= NGC(2) and NGC(1) and NGC(0) and NCI;
    AE <= NGC(1) and NPC(1);
    AF <= NGC(1) and NGC(0) and NPC(0);
    AG <= NGC(1) and NGC(0) and NCI;
    AH <= NGC(0) and NPC(0);
    AI <= NGC(0) and NCI;
end process misc2;
--*********************************************************************
misc3:process(LNGC,LNPC)
begin
    NGC(1 downto 0)<= LNGC;
    NPC(1 downto 0)<= LNPC;
end process misc3;
--*********************************************************************
end m3s011bo_rtl;
--*********************************************************************
