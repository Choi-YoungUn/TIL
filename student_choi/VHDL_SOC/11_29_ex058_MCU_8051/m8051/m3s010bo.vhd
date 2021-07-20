--Program Counter Control for M8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.009
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m3s010bo.vhd
--Author        :       K Dennis
--Library       :       WORK
--Created on    :       28th Dec 1995
--Purpose       :       PC control for M8051
--Version       :       1.009
--Mod Date      :       21st March 1997
--Mod History	:       1.009 STATDs 7-12 abandoned, redundant nets
--                            excised.
--                      1.008 Name change for Verilog translation
--                      1.007 PC MUX controls re-written for synthesis.
--                            EXT_PROG_EN and MOVC MUX moved in from
--                            m3s018bo. Program address busses revised.
--                            Sensitivity list revisions.
--                      1.006 ECN 878: Fast decision path for jump
--                            relatives
--			1.006 Unconditional look-ahead vector generation
--			1.005 OPH and OPL changed to DPH and DPL
--                      1.004-ECN 838 adjustment of OPC timing and
--                            dummy address cycle matching
--                      1.003- Change for download mode
--                      1.002-Calling file name changed to m8051.vhd
--                            LADD output removed
--                      1.001(Original)
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--                      :
--                      :
--Calls to              :m3s013bo.vhd
--                      :m3s011bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s010bo_e is 
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(EXT_PROG_EN,
            EXT_ROM:            
            out std_logic;
            DPL,
            DPH:
            out std_logic_vector(7 downto 0);
            STACK_DATA,
            PROGRAM_COUNT,
            PROGRAM_ADDR:
            out std_logic_vector(15 downto 0);
            NEA,
            LCYC,
            DLM,
            DLMSTB,
            INTA,
            IDLE,
	    C_TRUE,
            ADDR_11BIT,
            JMPADPTR,
            CLEAR,
            DIV2CK,
            NX1:
            in std_logic;
            VECTOR_ADDR:
            in std_logic_vector(4 downto 1);
            RDAT,
            ALUDAT,
            IMMDAT,
            RAMDI,
            MSIZ:
            in std_logic_vector(7 downto 0);
            CYC:
            in std_logic_vector(2 downto 1);
            OPC:
            in std_logic_vector(7 downto 5);
            PCADD:
            in std_logic_vector(12 downto 1);
            STATD:
            in std_logic_vector(6 downto 1);
            SFRW:
            in std_logic_vector(15 downto 14)
            );
end m3s010bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s010bo_rtl of m3s010bo_e is
--*********************************************************************
--*********************************************************************
-- Component Definitions
--*********************************************************************
--PC Inc/jump
component m3s011bo_e
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
end component;
--*********************************************************************
--pc mux
component m3s013bo_e
       port(NEXT_PROGRAM_COUNT:
            out std_logic_vector(15 downto 0);
            VECTOR_ADDR:
            in std_logic_vector(4 downto 1);
            IMMDAT,
            ALUDAT,
            RDAT:
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 5);
            NEXT_REL_PC:
            in std_logic_vector(15 downto 0);
            PCADD:
            in std_logic_vector(2 downto 1);
            NFBL,
            NFBH,
            SEL_11BIT_ADDR,
            INTA:
            in std_logic
            );
end component;
--*********************************************************************
--*********************************************************************
--signal definitions
--*********************************************************************
signal AG, BA, JMP_REL, L_EXT_ROM, PC_INCR: std_logic;
signal NFBH, NFBL, SEL_11BIT_ADDR:std_logic;
signal PROGRAM_COUNT_EN, STACK_DATA_EN, DPL_EN, DPH_EN:std_logic;
signal DPTR_DATA,LOCALA: std_logic_vector(7 downto 0);
signal ADDR_16BIT_LOW: std_logic_vector(7 downto 0);
signal NEXT_PROGRAM_COUNT, NEXT_PROGRAM_ADDR:std_logic_vector(15 downto 0);
signal NEXT_REL_PC, L_PROGRAM_COUNT:std_logic_vector(15 downto 0);
--*********************************************************************
--*********************************************************************
--port mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s011bo_e
  port map(
            NEXT_REL_PC => NEXT_REL_PC,
            PROGRAM_COUNT => L_PROGRAM_COUNT,
            IMMDAT => IMMDAT,
            PC_INCR => PC_INCR,
            JMP_REL => JMP_REL
           );
--*********************************************************************
U2:m3s013bo_e
  port map(
           NEXT_PROGRAM_COUNT => NEXT_PROGRAM_COUNT,
           VECTOR_ADDR => VECTOR_ADDR,
           IMMDAT => IMMDAT,
           ALUDAT => ALUDAT,
           RDAT => RDAT,
           OPC => OPC,
           NEXT_REL_PC => NEXT_REL_PC,
           PCADD => PCADD(2 downto 1),
           NFBL => NFBL,
           NFBH => NFBH,
           SEL_11BIT_ADDR => SEL_11BIT_ADDR,
           INTA => INTA
           );
--*********************************************************************

--*********************************************************************
--Process Definitions 
--*********************************************************************

--*********************************************************************
gen1:process(STATD,CYC,PCADD,SFRW,AG)
begin
   STACK_DATA_EN <= (CYC(1) and STATD(5) and PCADD(10))
                    or (CYC(1) and STATD(2));
   DPL_EN <= (SFRW(14) and PCADD(8)) or (AG and not PCADD(8));
   DPH_EN <= (SFRW(15) and PCADD(8)) or (STATD(6) and CYC(1) and not PCADD(8));
end process gen1;
--*********************************************************************
misc1:process(STATD,CYC,PCADD)
begin
   AG <= (CYC(1) and PCADD(7) and STATD(3)) or (CYC(2) and STATD(6) and not PCADD(7));
end process misc1;
--*********************************************************************
pc_load_controller:process(NX1)
-- Determine whether program counter loads from brancher/incrementer
-- (the default condition) or from another source.  Loading from
-- another source normally takes place for both bytes at c2s4p1,
-- with the exception of the JMP @A+DPTR instruction. 
-- These signals are registered to break a combinatorial path from
-- the opcode to the program counter, for the benefit of synthesis
-- tools.
-- Jump and call instructions using 11-bit addresses load upper three
-- address bits from the opcode register.
begin
   if NX1'event and NX1 ='1' then   
      if DLM = '1' then
         NFBL <= '0';
         NFBH <= '0';
         SEL_11BIT_ADDR <= '0';
      elsif (STATD(2) and not DIV2CK) = '1' then 
         NFBL <= (CYC(2) xor JMPADPTR) and not PCADD(3);
         NFBH <= CYC(2) and not JMPADPTR and PCADD(4);
         SEL_11BIT_ADDR <= not DLM and CYC(2) and ADDR_11BIT;
      elsif (STATD(5) and not DIV2CK) = '1' then 
         NFBL <= '0';
         NFBH <= CYC(1) and JMPADPTR and PCADD(4);
         SEL_11BIT_ADDR <= '0'; 
      end if;
   end if; 
end process pc_load_controller;
--*********************************************************************
misc2:process(NX1)
-- Look ahead logic for program counter incrementer.
-- The program counter will always increment after an opcode load.
begin
   if NX1'event and NX1 ='1' then   
       if (STATD(1) and not DIV2CK) = '1' then 
           BA <= (PCADD(9) and CYC(1)) or (PCADD(11) and CYC(2));
       elsif (STATD(4)and not DIV2CK) = '1' then
           BA <= LCYC or (PCADD(10) and CYC(1));
       end if;
    end if; 
end process misc2;
--*********************************************************************
determine_carry:process(DLM,INTA,BA)
-- Determine whether a program counter increment is required.
begin
   PC_INCR <= DLM or (BA and not INTA);
end process determine_carry;
--*********************************************************************
set_rel:process(NX1)
-- Determine whether a relative jump calculation is required.
begin
   if NX1'event and NX1 ='1' then   
      if (DLM or (STATD(4) and not DIV2CK)) = '1' then
         JMP_REL <= '0';
      elsif (STATD(1) and not DIV2CK) = '1' then 
         JMP_REL <= CYC(2) and ( PCADD(5) or PCADD(12) );
      end if;
   end if; 
end process set_rel;
--*********************************************************************
pc_load_enable:process(DLM, STATD, IDLE, PCADD, CYC, C_TRUE)
-- Program counter is updated at the end of every S1P1 and S4P1
-- with the exception that no load takes place during conditional branch
-- instructions at C2S5P1 if the branch condition (C_TRUE) is not met.
begin
   PROGRAM_COUNT_EN <= not DLM and ((STATD(1) and not IDLE) or
                 (STATD(4) and ( CYC(1) or not(PCADD(5)) or C_TRUE) ));
end process pc_load_enable;
--*********************************************************************
update_program_counter:process(NX1)
-- The Program Counter is updated at the end of S1P1 and S4P1.
begin
   if NX1'event and NX1 ='1' then
      if (CLEAR and not DLM) = '1' then
         L_PROGRAM_COUNT <= "0000000000000000";
      elsif ((PROGRAM_COUNT_EN and DIV2CK) or DLMSTB)= '1' then
         L_PROGRAM_COUNT(15 downto 0) <= NEXT_PROGRAM_COUNT(15 downto 0);
      end if;
   end if;
end process update_program_counter; 
--********************************************************************* 
save_addr16_low: process(NX1)
-- save low part of 16-bit address from ALU in cycle 1 for use in
-- cycle 2.
begin
   if NX1'event and NX1 ='1' then
      if (CYC(1) and STATD(3) and not DIV2CK) = '1' then
         ADDR_16BIT_LOW <= ALUDAT;
      end if;
   end if;
end process save_addr16_low;
--********************************************************************* 
select_movc_addr: process(L_PROGRAM_COUNT, ALUDAT, ADDR_16BIT_LOW,
                         PCADD, CYC, STATD)
-- Multiplex MOVC address into next program address during cycle 2.
begin
   if (PCADD(6) and CYC(2) and STATD(1)) = '1' then
      NEXT_PROGRAM_ADDR(15 downto 8) <= ALUDAT;
      NEXT_PROGRAM_ADDR(7 downto 0) <= ADDR_16BIT_LOW;
   else
      NEXT_PROGRAM_ADDR <= L_PROGRAM_COUNT;
   end if;
end process select_movc_addr;
--********************************************************************* 
select_program_source: process(MSIZ, NEXT_PROGRAM_ADDR)
begin
   if NEXT_PROGRAM_ADDR(15 downto 8) > MSIZ then
      L_EXT_ROM <= '1';
   else
      L_EXT_ROM <= '0';
   end if;
end process select_program_source;
--********************************************************************* 
update_program_address: process(NX1)
-- program address updates at the end of every S1P2 and S4P2 and
-- generally follows the program counter except during MOVC and 
-- JMP@A+DPTR instructions.  Update external program memory enable.
begin
   if NX1'event and NX1 ='1' then
     if (CLEAR and not STATD(4) and not STATD(5) and not DLM) = '1' then
         PROGRAM_ADDR <= "0000000000000000";
         EXT_PROG_EN  <= '0';
      elsif ((( (STATD(1) and not (JMPADPTR and CYC(2)))
            or(STATD(4) and not (JMPADPTR and CYC(1)))  )
            and not DIV2CK) or DLM) = '1' then
         PROGRAM_ADDR <= NEXT_PROGRAM_ADDR;
         EXT_PROG_EN  <= (L_EXT_ROM or not NEA) and not DLM;
      end if;
   end if;
end process update_program_address;
--********************************************************************* 
save_stack_data:process(NX1)
begin
   if NX1'event and NX1 ='1' then
      if (STACK_DATA_EN  and DIV2CK)= '1' then
         STACK_DATA(15 downto 0) <= NEXT_REL_PC(15 downto 0);
      end if;
   end if;
end process save_stack_data; 
--********************************************************************* 
set_data_pointer:process(NX1)
-- load data pointer special function registers
begin
   if NX1'event and NX1 ='1' then
      if CLEAR = '1' then
         DPL <= "00000000";
         DPH <= "00000000";
      else
         if (DPL_EN and not DIV2CK) = '1' then
            DPL <= DPTR_DATA;
         end if;
         if (DPH_EN and not DIV2CK) = '1' then
            DPH <= DPTR_DATA;
         end if;
      end if;
   end if;
end process set_data_pointer; 
--********************************************************************* 
muxlocala:process(PCADD,IMMDAT,ALUDAT)
begin
   if PCADD(7) = '0' then
      LOCALA(7 downto 0) <= IMMDAT(7 downto 0);
   else
      LOCALA(7 downto 0) <= ALUDAT(7 downto 0);
   end if;
end process muxlocala;
--********************************************************************* 
muxop:process(PCADD,LOCALA,RAMDI)
begin
   if PCADD(8) = '0' then
      DPTR_DATA(7 downto 0) <= LOCALA(7 downto 0);
   else
      DPTR_DATA(7 downto 0) <= RAMDI(7 downto 0);
   end if;
end process muxop;
--********************************************************************* 
localout:process(L_PROGRAM_COUNT, L_EXT_ROM)
begin
   PROGRAM_COUNT <= L_PROGRAM_COUNT;
   EXT_ROM <= L_EXT_ROM;
end process localout;
--********************************************************************* 

--********************************************************************* 
end m3s010bo_rtl;
--*********************************************************************
