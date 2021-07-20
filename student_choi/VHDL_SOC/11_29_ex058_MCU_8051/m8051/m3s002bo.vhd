--M8051 ALU element
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All Rights reserved.
--v1.002
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s002bo.vhd
--Author        :       A. D'Sa
--Library       :       WORK
--Created on    :       1st Oct 1995
--Purpose       :       M8051 Megamacro ALU element 
--Version       :       1.002
--Mod Date      :       10th February 1997
--Mod History	:	Comments updated.
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m3s003bo.vhd
--Calls to              :None
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s002bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(P,
            CO:
            out std_logic;
            ALUC:
            in std_logic_vector(5 downto 0);
            A,
            B:
            in std_logic
            );
end m3s002bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s002bo_rtl of m3s002bo_e is
--*********************************************************************
signal AA,AB,AC,AD,AE,AF:std_logic;
--*********************************************************************
begin
--Notes
--SINGLE BIT ALU ELEMENT. ALUC CARRIES THE OPERATION CODE
--P IS THE PRODUCT.
--CO IS THE CARRY/BORROW OUT (NOTE BORROW IS INVERTED).
--OPERATION CODE
--      0 1 2 3 4 5 | OUTPUT
--      ------------+-------------
--      0 0 0 0 X X | 0
--      1 1 0 0 X X | NOT A
--      0 1 1 1 X X | A + B
--      0 1 0 1 X X | A EXOR B
--      0 0 1 1 X X | A
--      0 0 1 0 X X | A . B
--      1 0 1 0 X X | A - B
--      0 1 1 0 X X | B
--      X X X X 1 X | ENABLE CARRY
--      X X X X X 1 | ENABLE BORROW
--*********************************************************************
-- Process Definitions
--*********************************************************************
misc1:process(A, B, ALUC)
begin
   AA <= not A and not B and ALUC(0);
   AB <= not A and B and ALUC(1);
   AC <= A and B and ALUC(2);
   AD <= A and not B and ALUC(3);
   AE <= A and B and ALUC(4);
   AF <= A and not B and ALUC(5);
end process misc1;
--*********************************************************************
misc2:process(AA,AB,AC,AD,AE,AF)
begin
   P <= AA or AB or AC or AD;
   CO <= AE or AF;
end process misc2;
--*********************************************************************
--*********************************************************************
end m3s002bo_rtl;
--*********************************************************************


