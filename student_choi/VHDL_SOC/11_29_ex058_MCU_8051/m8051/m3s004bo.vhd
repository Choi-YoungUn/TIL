--Opcode Decoder for m8051
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved
--v1.007
--*********************************************************************
--%W% %G% SCCS Version Control
--File	        :       m3s004bo.vhd
--Author        :       K.Dennis
--Library       :       WORK
--Created on    :       23th September 1995
--Purpose       :       opcode decoder for m8051
--Version       :       1.007
--Mod Date      :       24th March 1997
--Mod History	:       1.007 PSW carry enable restricted.
--                      1.006 Name change for Verilog translation
--                      1.005 Sensitivity list revisions.
--                      1.004 ECN 878: CTRU and INTA removed from
--                            decoder.  RMW definition widened to
--                            include register instructions.
--                      1.003 ECN 842 -ORLC timing adjustment, 
--                            ECN      dummy address matching 
--                      1.002 Calling file name changed to m8051.vhd
--                      1.001 Original
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051.vhd
--Calls to              :None
--                      :
--                      :
--                      :
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************

entity m3s004bo_e is
--This MegaMacro(TM) Design ( m8051 v06.500 ) is licensed to samasic for incorporation or simulation--
-- at san24 nongseo ri kiheung eup kyungki do korea  only.--
--It is an infringment of the 3Soft Limited licence agreement for this material to be used on another node. --
--This file was extracted on workstation hostid 72774370--
       port(ACCADD:
            out std_logic_vector(9 downto 0);
            PCADD:
            out std_logic_vector(12 downto 1);
            REGADD:
            out std_logic_vector(10 downto 0);
            MOVX:
            out std_logic_vector(4 downto 0);
            ALUC: 
            out std_logic_vector(17 downto 0);
            CODAT,
            PSWC:
            out std_logic_vector(2 downto 0);
            TMPADD,
            SPC:
            out std_logic_vector(3 downto 0);
            ADDR_11BIT,
            JMPADPTR,
            LOGDI,
            GOCYC2,
            MULDIV,
            NMULAB,
            NDIVAB,
            DAA,
            CJNE,
            RETI,
            EITHER_RET,
            RMW,
            JBC,
            IMMB3,
            IMMB4:
            out std_logic;
            OPC:
            in std_logic_vector(7 downto 0);
            DAAL,
            DAAH:
            in std_logic
            );       
end m3s004bo_e;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m3s004bo_rtl of m3s004bo_e is
--*********************************************************************
--*********************************************************************
--Component Definitions
--*********************************************************************
--Decode matrix
component m3s022bo_e
       port(LODEC:
            out std_logic_vector(7 downto 0);
            HIDEC:
            out std_logic_vector(15 downto 0);
            OPC: 
            in std_logic_vector(7 downto 0)
            );
end component;
--*********************************************************************
component m3s024bo_e
       port(ALUC:
            out std_logic_vector(17 downto 0);
            LODEC_4TOF,
            NDIVAB,
            NDJNZD,
            NDJNZR,
            NMULAB,
            DAA,
            NLJMP,
            NLCALL,
            NOP16,
            NCPLB,
            NSETB,
            NSETC,
            NORLCN,
            NORLCB,
            NMOVCB,
            NCLRB,
            NCLRC,
            NANLCN,
            NANLCB,
            JBC,
            NCPLC:
            out std_logic;
            HIDEC:
            in std_logic_vector(15 downto 0);
            LODEC: 
            in std_logic_vector(5 downto 0);
            OPC:
            in std_logic_vector(3 downto 1);
            RET,
            RETI:
            in std_logic 
            );       
end component;
--*********************************************************************
component m3s033bo_e
       port(ACCADD:
            out std_logic_vector(9 downto 0);
            NMOVPC,
            NINCDP,
            NSWAPN,
            NMOVBC,
            LOGDI:
            out std_logic;
            HIDEC:
            in std_logic_vector(14 downto 0);
            LODEC: 
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 3);
            LODEC_4TOF,
            NOP16,
            MULDIV,
            INDXR,
            INDOP,
            NDIV,
            NDJD,
            NDJR,
            NBEN,
            CJNE,
            NMUL,
            NMCB:
            in std_logic 
            );       
end component;
--*********************************************************************
component m3s032bo_e
       port(TMPADD:
            out std_logic_vector(3 downto 0);
            PCLONG,
            LO5TOF,
            NLOGDA:
            out std_logic;
            HIDEC:
            in std_logic_vector(11 downto 2);
            LODEC: 
            in std_logic_vector(5 downto 2);
            LODEC_4TOF,
            ND16,
            MULDIV,
            NMPC,
            NLCA,
            NLJM,
            EITHER_RET,
            LOGDI:
            in std_logic 
            );       
end component;
--*********************************************************************
component m3s034bo_e
       port(PCADD:
            out std_logic_vector(12 downto 1);
            HIDEC:
            in std_logic_vector(15 downto 0);--bits 4 to 6 and 12,13 not used
            LODEC:
            in std_logic_vector(5 downto 0);
            OPC:
            in std_logic_vector(7 downto 3);--bits and 3 only used
            NLCALL,
            BRET,
            PCL0,
            DJNZ,
            CJNE,
            NIDP,
            INDOP,
            LOGDI,
            NDJR,
            NDJD:
            in std_logic 
            );       
end component;
--*********************************************************************
component m3s035bo_e
       port(REGADD:
            out std_logic_vector(10 downto 0);
            NCALL,
            NPOP,
            NPUSH:
            out std_logic;
            HIDA:
            in std_logic_vector(3 downto 0);
            LODEC:
            in std_logic_vector(2 downto 0);
            OPC:
            in std_logic_vector(4 downto 3);
            HIDB:
            in std_logic_vector(8 downto 7);
            HIDC:
            in std_logic_vector(13 downto 10);
            HI15,
            L5TF,
            NLCA,
            BRET,
            INDOP,
            INDXR,
            INDXW,
            NLDA,
            LOGDI,
            NMBC,
            JBC,
            NBEN,
            NSWA,
            NMCB:
            in std_logic
            );       
end component;
--*********************************************************************
--Signal definitions
--*********************************************************************
signal AB,AC,INDIRECT_OPS,MOVDAI,AI,AJ,AK,AM,AN: std_logic;
signal AU,AV,AW,AX,AY,MOVRDA,BA: std_logic;
signal ARITH_OPS, CARRY_OPS1, CARRY_OPS2, CARRY_OPS3: std_logic;
signal LODEC_4TOF, LDAA, NLJMP, NOP16, LNMULAB, LNDIVAB: std_logic;
signal NCPLB, NSETB, NSETC, NMOVCB, NMOVBC, NCLRB, NCLRC: std_logic;
signal NORLCN, NORLCB, NANLCN, NANLCB: std_logic;
signal LJBC, NCPLC, NMOVPC, NINCDP, NSWAPN: std_logic;
signal LLOGDI, LCJNE, NDJNZD, NDJNZR, DJNZ: std_logic;
signal PCLONG, LO5TOF, NLOGDA, LMULDIV: std_logic;
signal NCALL, NLCALL, LRET, LRETI, LEITHER_RET, NPOP, NPUSH: std_logic;
signal LLODEC: std_logic_vector(7 downto 0);
signal HIDEC:  std_logic_vector(15 downto 0);
signal LALUC:  std_logic_vector(17 downto 0);
--*********************************************************************
--Port Mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s022bo_e
port map(
         LODEC => LLODEC,
         HIDEC => HIDEC, 
         OPC => OPC 
         );
--*********************************************************************
U2:m3s024bo_e
port map(
         ALUC => LALUC,
         LODEC_4TOF => LODEC_4TOF,
         NDIVAB => LNDIVAB,
         NDJNZD => NDJNZD,
         NDJNZR => NDJNZR,
         NMULAB => LNMULAB,
         DAA => LDAA,
         NLJMP => NLJMP,
         NLCALL => NLCALL,
         NOP16 => NOP16,
         NCPLB => NCPLB,
         NSETB => NSETB,
         NSETC => NSETC,
         NORLCN => NORLCN,
         NORLCB => NORLCB,
         NMOVCB => NMOVCB,
         NCLRB => NCLRB,
         NCLRC => NCLRC,
         NANLCN => NANLCN,
         NANLCB => NANLCB,
         JBC => LJBC,
         NCPLC => NCPLC,
         HIDEC => HIDEC,
         LODEC(5 downto 0) => LLODEC(5 downto 0), 
         OPC(3 downto 1) => OPC(3 downto 1),
         RET => LRET,
         RETI => LRETI 
         );   
--*********************************************************************
U3:m3s033bo_e
port map(
         ACCADD => ACCADD,
         NMOVPC => NMOVPC,
         NINCDP => NINCDP,
         NSWAPN => NSWAPN,
         NMOVBC => NMOVBC,
         LOGDI => LLOGDI,
         HIDEC(14 downto 0) => HIDEC(14 downto 0),
         LODEC => LLODEC,
         OPC(7 downto 3) => OPC(7 downto 3),
         LODEC_4TOF => LODEC_4TOF,
         NOP16 => NOP16,
         MULDIV => LMULDIV,
         INDXR => AI,
         INDOP => INDIRECT_OPS,
         NDIV => LNDIVAB,
         NDJD => NDJNZD,
         NDJR => NDJNZR,
         NBEN => LALUC(17),
         CJNE => LCJNE,
         NMUL => LNMULAB,
         NMCB => NMOVCB
         );   
--*********************************************************************
U4:m3s032bo_e
port map(
         TMPADD => TMPADD,
         PCLONG => PCLONG,
         LO5TOF => LO5TOF,
         NLOGDA => NLOGDA,
         HIDEC(11 downto 2) => HIDEC(11 downto 2),
         LODEC(5 downto 2) => LLODEC(5 downto 2),
         LODEC_4TOF => LODEC_4TOF,
         ND16 => NOP16,
         MULDIV => LMULDIV,
         NMPC => NMOVPC,
         NLCA => NLCALL,
         NLJM => NLJMP,
         EITHER_RET => LEITHER_RET,
         LOGDI => LLOGDI
         );    
--*********************************************************************
U5:m3s034bo_e
port map(
         PCADD => PCADD,
         HIDEC(15 downto 0) => HIDEC(15 downto 0),
         LODEC(5 downto 0) => LLODEC(5 downto 0),
         OPC(7 downto 3) => OPC(7 downto 3),
         NLCALL => NLCALL,
         BRET => LEITHER_RET,
         PCL0 => PCLONG,
         DJNZ => DJNZ,
         CJNE => LCJNE,
         NIDP => NINCDP,
         INDOP => INDIRECT_OPS,
         LOGDI => LLOGDI,
         NDJR => NDJNZR,
         NDJD => NDJNZD
         );       
--*********************************************************************
U6:m3s035bo_e
port map( 
         REGADD => REGADD,
         NCALL => NCALL,
         NPOP => NPOP,
         NPUSH => NPUSH,
         HIDA => HIDEC(3 downto 0),
         LODEC(2 downto 0) => LLODEC(2 downto 0),
         OPC(4 downto 3) => OPC(4 downto 3),
         HIDB => HIDEC(8 downto 7),
         HIDC => HIDEC(13 downto 10),
         HI15 => HIDEC(15),
         L5TF => LO5TOF,
         NLCA => NLCALL,
         BRET => LEITHER_RET,
         INDOP => INDIRECT_OPS,
         INDXR => AI,
         INDXW => AJ,
         NLDA => NLOGDA,
         LOGDI => LLOGDI,
         NMBC => NMOVBC,
         JBC => LJBC,
         NBEN => LALUC(17),
         NSWA => NSWAPN,
         NMCB => NMOVCB
         );       
--*********************************************************************
--Notes
--       
--*********************************************************************
--Process Definitions
--*********************************************************************
misc1:process(LNMULAB,HIDEC,LLODEC,NOP16,NORLCB,NLJMP,NLCALL,NMOVBC)
begin
   AB <= LLODEC(1) or (LLODEC(0) and not HIDEC(0));
   AC <= NOP16 and LNMULAB and NORLCB and NLJMP and NLCALL and NMOVBC;
end process misc1;
--*********************************************************************
misc2:process(HIDEC, LLODEC, OPC, LODEC_4TOF)
begin
   LCJNE <= HIDEC(11) and LODEC_4TOF;
   LRET <=  HIDEC(2) and LLODEC(2);
   LRETI <= HIDEC(3) and LLODEC(2);
   LEITHER_RET <= not OPC(7) and not OPC(6) and OPC(5) and LLODEC(2);
   INDIRECT_OPS <= OPC(1) and OPC(2) and (not OPC(3));
   MOVDAI <= HIDEC(7) and LLODEC(5);
   AI <= HIDEC(14) and (LLODEC(2) or LLODEC(3));
   AJ <= HIDEC(15) and (LLODEC(2) or LLODEC(3));
   AK <= (HIDEC(0) or HIDEC(1)) and LODEC_4TOF;
   
end process misc2;
--*********************************************************************
misc3:process(HIDEC, LLODEC, OPC, DAAL, DAAH, NDJNZR, NDJNZD, LDAA,
              INDIRECT_OPS, LODEC_4TOF)
begin
    DJNZ <= not(NDJNZR and NDJNZD);
    AM <= DAAL and LDAA;
    AN <= DAAH and LDAA;
    ARITH_OPS <= (HIDEC(2) or HIDEC(3) or HIDEC(9)) and LODEC_4TOF;
    CARRY_OPS1 <= HIDEC(11) and LODEC_4TOF;
    CARRY_OPS2 <= (HIDEC(1) or HIDEC(3)) and LLODEC(3);
    AU <= HIDEC(14) and LLODEC(0);
    AV <= HIDEC(15) and LLODEC(0);
    AY <= (HIDEC(0) or HIDEC(1)) and LLODEC(5);
    MOVRDA <= (OPC(3) or INDIRECT_OPS) and HIDEC(10);

end process misc3;
--*********************************************************************
misc4:process(NORLCN,NANLCN,NORLCB,NANLCB,NMOVCB,NCPLC,NCLRC,NSETC)
begin
    CARRY_OPS3 <= not(NORLCN and NANLCN and NORLCB and NANLCB and NMOVCB
                      and NCPLC and NCLRC and NSETC);
end process misc4;
--*********************************************************************
misc5:process(AI,AJ,LJBC,NLOGDA,NMOVBC,NCPLB,NCLRB,NSETB,NDJNZD,LLOGDI)
begin
    AW <= (not AI) and (not AJ);
    AX <= (not LJBC) and NLOGDA and NMOVBC and NCPLB and NCLRB and NSETB and NDJNZD and not LLOGDI;
end process misc5;
--*********************************************************************
misc6:process(LCJNE, LEITHER_RET, MOVRDA, MOVDAI, LLOGDI)
begin
    BA <= LCJNE or LEITHER_RET or MOVRDA or MOVDAI or LLOGDI;
end process misc6;
--*********************************************************************
out1:process(AB, AC, AI, AJ, AY, AX, BA, LDAA, NOP16, LNDIVAB, LNMULAB,
             HIDEC, LLODEC, LLOGDI, LCJNE, PCLONG, NDJNZD, OPC, DJNZ)
begin
   GOCYC2 <= AB or not AC or AI or AJ or BA or HIDEC(8) or DJNZ;
   LMULDIV <=  not(LNDIVAB and LNMULAB); 
   DAA <= LDAA;
   RMW <= AY or not AX or (OPC(4) and (HIDEC(0) or HIDEC(1) or HIDEC(13)));
   IMMB3 <= (LLODEC(0) and (HIDEC(1) or HIDEC(2) or HIDEC(3) or HIDEC(9))) or
           ((HIDEC(7) or HIDEC(8)) and LLODEC(5)) or LCJNE or LLOGDI or PCLONG or not NDJNZD;
   IMMB4 <= not NOP16;
   JMPADPTR <= HIDEC(7) and LLODEC(3);
end process out1;
--*********************************************************************
alucout:process(LALUC)
begin
   ALUC <= LALUC;
end process alucout;
--*********************************************************************
codatout:process(AK, DJNZ, AM, AN)
begin
    CODAT(0) <= AK or DJNZ;
    CODAT(1) <= AM;
    CODAT(2) <= AN;
end process codatout; 
--*********************************************************************
movx_control:process(AU,AV,AW,AJ,AI)
-- External data access (MOVX) controller
-- 
-- Bit Definitions:
-- MOVX(0): Enable MOVX
-- MOVX(1): MOVX @Ri
-- MOVX(2): MOVX @DPTR
-- MOVX(3): MOVX WRITE
-- MOVX(4): MOVX READ
-- 
begin
   MOVX(0) <= AU or AV or not AW;
   MOVX(1) <= not AW;
   MOVX(2) <= AU or AV;
   MOVX(3) <= AV or AJ;
   MOVX(4) <= AU or AI;
end process movx_control;
--*********************************************************************
psw_control:process(ARITH_OPS, LMULDIV, LDAA, CARRY_OPS1, CARRY_OPS2,
                    CARRY_OPS3)
-- Program Status Word Flag Controller
-- 
-- Bit Definitions:
-- PSWC(0): Enable Overflow Flag Load.
-- PSWC(1): Enable Half-Carry Flag Load,
-- PSWC(2): Enable Carry Flag Load,
--
begin
   PSWC(0) <= ARITH_OPS or LMULDIV;
   PSWC(1) <= ARITH_OPS;
   PSWC(2) <= ARITH_OPS or LMULDIV or LDAA or CARRY_OPS1 or CARRY_OPS2
              or CARRY_OPS3;
end process psw_control;
--*********************************************************************
spc_control:process(LEITHER_RET, NPOP, NPUSH, NCALL)
-- Stack Pointer Load, Increment and Decrement Controller
--
-- Bit Definitions:
-- SPC(0): Stack Pointer Decrement
-- SPC(1): Stack Pointer Increment
-- SPC(2): Clock Stack Pointer in Machine Cycle 1 
-- SPC(3): Clock Stack Pointer in Machine Cycle 2 

begin
   SPC(0) <= LEITHER_RET or not NPOP;
   SPC(1) <= not(NPUSH and NCALL);
   SPC(2) <= not NPUSH or not NCALL or LEITHER_RET; 
   SPC(3) <= not NCALL or not NPOP or LEITHER_RET;
end process spc_control;
--*********************************************************************
--localout:process(LLODEC,LLOGDI,LMULDIV, LJBC, LCJNE, LNMULAB, LNDIVAB, LRETI, LEITHER_RET)
-- Map local signal names to global names
--begin
ADDR_11BIT <= LLODEC(1);
LOGDI <= LLOGDI;
MULDIV <= LMULDIV;
NMULAB <= LNMULAB;
NDIVAB <= LNDIVAB;
JBC <= LJBC;
CJNE <= LCJNE;
RETI <= LRETI;
EITHER_RET <= LEITHER_RET;
--end process localout;
--*********************************************************************
end m3s004bo_rtl;
--*********************************************************************
