--M8051 Megamacro Top Level
--(c) Copyright Mentor Graphics Corporation and Licensors 1997. All rights reserved.
--v1.012
--*********************************************************************
--%W% %G% SCCS Version Control

--File	        :       m8051.vhd
--Author        :       Ken Dennis
--Library       :       WORK
--Created on    :       9th January 1996
--Purpose       :       M8051 Megamacro 
--Version       :       1.012
--Mod Date      :       14th April 1997
--Mod History	:       1.012 Redundant signals removed, comments added.
--                      1.011 SFR Expansion Capability
--                      1.010 Name change for Verilog translation.
--                      1.009 Name changes and exports.
--                            Program counter revisions.
--                            Sensitivity list revisions.
--                            Use accumulator not ALUDAT for MOVX writes
--                      1.008 ECN 878: PCADD bus width increased, C_TRUE
--                            inserted into m3s010bo and m3s008bo.
--                            Read Modify Write affects timer counters. 
--                      1.007 LDV1 renamed LOV1
--			1.006 Idle Mode Power Saving Scheme
--			1.005-ACCO changed to ACC0,OPH,OPL changed
--                            to DPH and DPL 
--                            ECN 863 ALEN brought forward to end of reset   
--                      1.004-ECN838 adjustment to OPC timing
--                           -and dummy address matching 
--                      1.003-Change to download mode
--                      1.002-File name changed from m3s000bo.vhd
--                      1.001(Original)
--
--
--
--*********************************************************************
--Hierarchy record      :
--Called by             :m8051_tb.vhd
--Calls to              :m3s001bo.vhd
--                      :m3s003bo.vhd
--                      :m3s004bo.vhd
--                      :m3s005bo.vhd
--                      :m3s006bo.vhd
--                      :m3s007bo.vhd
--                      :m3s008bo.vhd
--                      :m3s010bo.vhd
--                      :m3s015bo.vhd
--                      :m3s018bo.vhd
--                      :m3s019bo.vhd
--                      :m3s020bo.vhd
--                      :m3s023bo.vhd
--                      :m3s025bo.vhd
--                      :m3s028bo.vhd
--*********************************************************************
library IEEE;

use IEEE.std_logic_1164.all;
library WORK;

--*********************************************************************
--Entity Definition
--*********************************************************************
entity m8051 is 
       port(
            NMOE,
            NMWE,
            DLM,
            ALE,
            NPSEN,
            NALEN,
            NFWE,
            NFOE,
            NSFRWE,
            NSFROE,
            IDLE,
            XOFF: out std_logic;
            OA,
            OB,
            OC,
            OD,
            AE,
            BE,
            CE,
            DE,
            FA,
            FO: out std_logic_vector(7 downto 0);
            M: out std_logic_vector(15 downto 0);
            NX1,
            NX2,
            RST,
            NEA,
            NESFR,
            ALEI,
            PSEI: in std_logic;
            AI,
            BI,
            CI,
            DI,
            FI,
            MD: in std_logic_vector(7 downto 0)
            );
end m8051;
--*********************************************************************
--Architecture definition
--*********************************************************************
architecture m8051_rtl of m8051 is
--*********************************************************************
--*********************************************************************
--Component Definitions
--*********************************************************************
--Clock Generator
component m3s001bo_e
       port(STATD:
            out std_logic_vector(6 downto 1);
            CYC:
            out std_logic_vector(3 downto 1);
            LCYC,
            DIV2CK1,
            DIV2CK2,
            S_EN,
            T_EN,
            STATE12: 
            out std_logic;
            RST,
            GOCYC2,
            MULDIV,
            NX1,
            NX2:
            in std_logic;
            PCON:
            in std_logic_vector(0 downto 0)
            );
end component;
--*********************************************************************
--ALU
component m3s003bo_e
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
end component;
--*********************************************************************
--Opcode decode
component m3s004bo_e
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
            PSWC,
            CODAT:
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
end component;
--*********************************************************************
--Accumulator and ALU Input Temporary Register Number 2
component m3s005bo_e
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
end component;
--*********************************************************************
-- ALU Input Temporary Register Number 1
component m3s006bo_e
       port(TMPDAT:
            out std_logic_vector(7 downto 0);
            PROGRAM_COUNT:
            in std_logic_vector(15 downto 0);
            RDAT,
            IMMDAT,
            DPH,
            DPL,
            BREG:
            in std_logic_vector(7 downto 0);
            TMPADD:
            in std_logic_vector(3 downto 0);
            CODAT:
            in std_logic_vector(2 downto 0);
            CYC:
            in std_logic_vector(1 downto 1);
            STATD:
            in std_logic_vector(5 downto 2);
            LOGDI,
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );
end component;
--*********************************************************************
--Conditional Branch Test
component m3s007bo_e
       port(C_TRUE:
            out std_logic;
            ALUDAT:
            in std_logic_vector(7 downto 0);
            OPC:
            in std_logic_vector(7 downto 4);
            PSWDAT:
            in std_logic_vector(7 downto 7);
            CYC:
            in std_logic_vector(2 downto 2);
            STATD:
            in std_logic_vector(3 downto 3);
            BBIT,
            DIV2CK,
            NX1,
            RST:
            in std_logic 
            );    
end component;
--*********************************************************************
--Register control
component m3s008bo_e
       port(WEP,
            NFOE,
            NFWE,            
            NSFROE,
            NSFRWE:
            out std_logic;
            BIT_POSN:
            out std_logic_vector(2 downto 0);
            RAMDI,
            FA,
            RDAT:
            out std_logic_vector(7 downto 0);
            SFRW:
            out std_logic_vector(21 downto 0);
            JBC,
            EITHER_RET,
            C_TRUE,
            NESFR,
            CLEAR,
            LCYC,
            RESINT,
            DIV2CK,
            NX1,
            RST:
            in std_logic;
            ALUDAT,
            IMMDAT,
            SFRDAT,
            SP,
            IROMD,
            FI:
            in std_logic_vector(7 downto 0);
            CYC:
            in std_logic_vector(2 downto 1);
            OPC:
            in std_logic_vector(3 downto 0);
            PSWDAT:
            in std_logic_vector(4 downto 3);
            REGADD:
            in std_logic_vector(10 downto 0);
            STATD:
            in std_logic_vector(6 downto 1);
            STACK_DATA:
            in std_logic_vector(15 downto 0)
            );
end component;
--*********************************************************************
--Program counter control
component m3s010bo_e
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
end component;
--*********************************************************************
--Timer counter
component m3s015bo_e
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
end component;
--*********************************************************************
--I/O port control
component m3s018bo_e
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
end component;
--*********************************************************************
--Interrupt control
component m3s019bo_e
       port(INTA:            
            out std_logic;
            IE,
            IP:
            out std_logic_vector(7 downto 0);
            VECTOR_ADDR:
            out std_logic_vector(4 downto 1);
            IACK:
            out std_logic_vector(3 downto 0);
            RITI,
            WEP,
            RETI,
            LCYC,
            T_EN,
            S_EN,
            DIV2CK,
            CLEAR,
            RST,
            NX1,
            NX2:
            in std_logic;
            STATD:
            in std_logic_vector(1 downto 1);
            CYC:
            in std_logic_vector(2 downto 2);
            TCON: --even bits not used
            in std_logic_vector(7 downto 1);
            RAMDI:
            in std_logic_vector(7 downto 0);
            SFRW:
            in std_logic_vector(13 downto 12)
            );
end component;
--*********************************************************************
--miscellaneous special function registers
component m3s020bo_e
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
end component;
--*********************************************************************
--special function register output multiplexer
component m3s023bo_e
       port(SFRDAT:
            out std_logic_vector(7 downto 0);
            FA:
            in std_logic_vector(6 downto 0);
            PORTA,
            PORTB,
            PORTC,
            PORTD,
            SP,
            DPL,
            DPH,
            PCON,
            TCON,
            TMOD,
            TLA,
            TLB,
            THA,
            THB,
            SCON,
            SBUF,
            IE,
            IP,
            PSWDAT,
            ACCDAT,
            BREG,
            MSIZ:
            in std_logic_vector(7 downto 0)
            );       
end component;
--*********************************************************************
--Opcode Register
component m3s025bo_e
       port(OPC:
            out std_logic_vector(7 downto 0);
            OPLOAD:
            out std_logic;
            IROMD:
            in std_logic_vector(7 downto 0);
            STATD:
            in std_logic_vector(1 downto 1);
            PCON:
            in std_logic_vector(0 downto 0);
            CLEAR,
            RST,
            DIV2CK,
            NX1,
            INTA,
            LCYC,
            DLM:
            in std_logic
            );
end component;
--*********************************************************************
--UART
component m3s028bo_e
       port(SCON,
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
end component;
--*********************************************************************
--Signal definitions
--*********************************************************************
signal DIV2CK1, DIV2CK2, CLEAR:std_logic;
signal NMULAB,NDIVAB:std_logic;
signal LCYC,GOCYC2,MULDIV,S_EN,T_EN,STATE12,LOGDI:std_logic;
signal C_TRUE,DAAL,DAAH,DAA,EXPMEM,INTA,OPLOAD,RETI,RMW,PAR:std_logic;
signal ACC0,ACO,BBIT,CO,IMMB3,IMMB4,OV,RESINT,WEP:std_logic;
signal DLMR,DLMSTB,DLMSTBI,RITI,RXDO,TXDO:std_logic;
signal LOV1,MOEI:std_logic;
signal IMMDATEN,JMPADPTR:std_logic;
signal LDLM, EXT_PROG_EN, EXT_ROM:std_logic;
signal JBC, CJNE, EITHER_RET:std_logic;
signal ADDR_11BIT:std_logic;
signal CODAT,BIT_POSN,PSWC:std_logic_vector(2 downto 0);
signal DLMSTQ: std_logic_vector(2 downto 0);
signal CYC:std_logic_vector(3 downto 1);
signal IACK,SPC,TMPADD:std_logic_vector(3 downto 0);
signal VECTOR_ADDR:std_logic_vector(4 downto 1);
signal MOVX:std_logic_vector(4 downto 0);
signal ACCDAT,ALUDAT,BREG,CPRDDM,IE,IP:std_logic_vector(7 downto 0);
signal IMMDAT,IROMD,MSIZ,OPC,DPH,DPL,OAI:std_logic_vector(7 downto 0);
signal PCON,PSWDAT,RAMDI,RDAT,SBUF,SCON:std_logic_vector(7 downto 0);
signal PORTA,PORTB,PORTC,PORTD:std_logic_vector(7 downto 0);
signal SFRDAT,SP,TCON,TLA,TLB,THA,THB,TMOD,TMPDAT:std_logic_vector(7 downto 0);
signal LFA:std_logic_vector(7 downto 0);
signal ACCADD:std_logic_vector(9 downto 0);
signal ACLDAT:std_logic_vector(9 downto 0);
signal PCADD:std_logic_vector(12 downto 1);
signal REGADD:std_logic_vector(10 downto 0);
signal STATD:std_logic_vector(6 downto 1);
signal STACK_DATA, PROGRAM_COUNT, PROGRAM_ADDR:std_logic_vector(15 downto 0);
signal ALUC:std_logic_vector(17 downto 0);
signal SFRW:std_logic_vector(21 downto 0);
--*********************************************************************
--Port Mapping
--*********************************************************************
begin
--*********************************************************************
U1:m3s001bo_e
port map(
         STATD => STATD,
         CYC => CYC,
         LCYC => LCYC,
         DIV2CK1 => DIV2CK1,
         DIV2CK2 => DIV2CK2,
         S_EN => S_EN,
         T_EN => T_EN,
         STATE12 => STATE12, 
         RST => RST,
         GOCYC2 => GOCYC2,
         MULDIV => MULDIV,
         PCON(0) => PCON(0),
         NX1 => NX1,
         NX2 => NX2
         );
--*********************************************************************
U2:m3s003bo_e
port map(
         ALUDAT => ALUDAT,
         CPRDDM => CPRDDM,
         CO => CO,
         ACO => ACO,
         OV => OV,
         BBIT => BBIT,
         ACLDAT => ACLDAT,
         TMPDAT => TMPDAT,
         ALUC => ALUC,
         ACCDAT => ACCDAT(7 downto 7),
         BIT_POSN => BIT_POSN,
         NMULAB => NMULAB,
         NDIVAB => NDIVAB,
         DAA => DAA,
         ACC0 =>ACC0
         );
--*********************************************************************
U3:m3s004bo_e
port map(
         ACCADD => ACCADD,
         PCADD => PCADD,
         REGADD => REGADD,
         TMPADD => TMPADD,
         MOVX => MOVX,
         ALUC => ALUC, 
         CODAT => CODAT,
         PSWC => PSWC,
         SPC => SPC,
         ADDR_11BIT => ADDR_11BIT,
         LOGDI => LOGDI,
         JMPADPTR =>JMPADPTR,
         GOCYC2 => GOCYC2,
         MULDIV => MULDIV,
         NMULAB => NMULAB,
         NDIVAB => NDIVAB,
         DAA => DAA,
         CJNE => CJNE,
         RETI => RETI,
         EITHER_RET => EITHER_RET,
         RMW => RMW,
         JBC => JBC,
         IMMB3 => IMMB3,
         IMMB4 => IMMB4,
         OPC => OPC,
         DAAL => DAAL,
         DAAH => DAAH
         );
--*********************************************************************
U4:m3s005bo_e
port map(
         ACCDAT => ACCDAT,
         BREG => BREG,
         ACLDAT => ACLDAT,
         PAR => PAR,
         ACC0 => ACC0,
         DAAL => DAAL,
         DAAH => DAAH,
         CYC => CYC(1 downto 1),
         PSWDAT => PSWDAT(7 downto 6),
         STATD => STATD(6 downto 2),
         ACCADD => ACCADD,
         ALUDAT => ALUDAT,
         CPRDDM => CPRDDM,
         RDAT => RDAT,
         IMMDAT => IMMDAT,
         RAMDI => RAMDI,
         SFRW => SFRW(21 downto 20),
         DAA => DAA,
         LCYC => LCYC,
         DIV2CK => DIV2CK2,
         CO => CO,
         RST => RST,
         NX1 => NX2
         ); 
--*********************************************************************
U5:m3s006bo_e
port map(
         TMPDAT => TMPDAT,
         PROGRAM_COUNT => PROGRAM_COUNT,
         RDAT => RDAT,
         IMMDAT => IMMDAT,
         CODAT => CODAT,
         DPH => DPH,
         DPL => DPL,
         BREG => BREG,
         TMPADD => TMPADD,
         CYC => CYC(1 downto 1),
         STATD => STATD(5 downto 2),
         LOGDI => LOGDI,
         DIV2CK => DIV2CK2,
         NX1 => NX2,
         RST => RST
         );       
--*********************************************************************
U6:m3s007bo_e
port map(
         C_TRUE => C_TRUE,
         ALUDAT => ALUDAT,
         OPC => OPC(7 downto 4),
         PSWDAT => PSWDAT(7 downto 7),
         CYC => CYC(2 downto 2),
         STATD => STATD(3 downto 3),
         BBIT => BBIT,
         DIV2CK => DIV2CK2,
         NX1 => NX2,
         RST => RST
         );    
--*********************************************************************
U7:m3s008bo_e
port map(
         WEP => WEP,
         NFOE => NFOE,
         NFWE => NFWE,            
         NSFROE => NSFROE,
         NSFRWE => NSFRWE,
         RAMDI => RAMDI,
         FA => LFA,
         BIT_POSN => BIT_POSN,
         RDAT => RDAT,
         SFRW => SFRW,
         JBC => JBC,
         EITHER_RET => EITHER_RET,
         C_TRUE => C_TRUE,
         NESFR => NESFR,
         CLEAR => CLEAR,
         LCYC => LCYC,
         RESINT => RESINT,
         DIV2CK => DIV2CK2,
         NX1 => NX2,
         RST => RST,
         ALUDAT => ALUDAT,
         IMMDAT => IMMDAT,
         SFRDAT => SFRDAT,
         SP => SP,
         IROMD => IROMD,
         FI => FI,
         CYC => CYC(2 downto 1),
         OPC => OPC(3 downto 0),
         PSWDAT => PSWDAT(4 downto 3),
         REGADD => REGADD, 
         STATD => STATD(6 downto 1),
         STACK_DATA => STACK_DATA
         );
--*********************************************************************
U8:m3s010bo_e
port map(
         EXT_PROG_EN => EXT_PROG_EN,
         EXT_ROM => EXT_ROM,
         DPL => DPL,
         DPH => DPH,
         STACK_DATA => STACK_DATA,
         PROGRAM_COUNT => PROGRAM_COUNT,
         PROGRAM_ADDR => PROGRAM_ADDR,
         NEA => NEA,
         LCYC => LCYC,
         DLM => LDLM,
         DLMSTB => DLMSTB,
         INTA => INTA,
         IDLE => PCON(0),
         C_TRUE => C_TRUE,
         CLEAR => CLEAR,
         DIV2CK => DIV2CK2,
         NX1 => NX2,
         RDAT => RDAT,
         ALUDAT => ALUDAT,
         IMMDAT => IMMDAT,
         VECTOR_ADDR => VECTOR_ADDR,
         RAMDI => RAMDI,
         MSIZ => MSIZ,
         CYC => CYC(2 downto 1),
         OPC => OPC(7 downto 5),
         PCADD => PCADD,
         ADDR_11BIT => ADDR_11BIT,
         JMPADPTR => JMPADPTR,
         STATD => STATD(6 downto 1),
         SFRW => SFRW(15 downto 14)
         );
--*********************************************************************
U9:m3s015bo_e
port map(
         LOV1 => LOV1,
         TCON => TCON,
         TMOD => TMOD,
         TLA => TLA,
         TLB => TLB,
         THA => THA,
         THB => THB,
         IACK => IACK,
         DI => DI(5 downto 2),
         STATD => STATD(6 downto 6),
         RAMDI => RAMDI,
         SFRW => SFRW(9 downto 4),
         RMW => RMW,
         S_EN => S_EN,
         T_EN => T_EN,
         STATE12 => STATE12,
         DIV2CK1 => DIV2CK1,
         NX1 => NX1,
         NX2 => NX2,
         CLEAR => CLEAR
         );
--*********************************************************************
U10:m3s018bo_e
port map(
         ALE => ALE,
         NPSEN => NPSEN,
         MOEI => MOEI,
         EXPMEM =>EXPMEM,
         OAI => OAI,
         OB => OB,
         OC => OC,
         OD => OD,
         AE => AE,
         BE => BE,
         CE => CE,
         DE => DE,
         PORTA => PORTA,
         PORTB => PORTB,
         PORTC => PORTC,
         PORTD => PORTD,
         PROGRAM_ADDR => PROGRAM_ADDR,
         AI => AI,
         BI => BI,
         CI =>CI,
         DI => DI,
         RAMDI => RAMDI,
         DPL => DPL,
         DPH => DPH,
         ACCDAT => ACCDAT,
         FA => LFA,
         STATD => STATD(6 downto 1),
         MOVX => MOVX,
         SFRW => SFRW(3 downto 0),
         CYC => CYC(2 downto 1),
         PCON => PCON(0 downto 0),
         XROM => EXT_ROM,
         EXT_PROG_EN => EXT_PROG_EN,
         NEA => NEA,
         RXDO => RXDO,
         TXDO => TXDO,
         RMW => RMW,
         DIV2CK => DIV2CK2,
         NX1 => NX1,
         NX2 => NX2,
         CLEAR => CLEAR,
         RST => RST,
         DLMR => DLMR
         );
--*********************************************************************
U11:m3s019bo_e
port map(
         INTA => INTA,            
         IE => IE,
         IP => IP,
         VECTOR_ADDR => VECTOR_ADDR,
         IACK => IACK,
         RITI => RITI,
         WEP => WEP,
         RETI => RETI,
         LCYC => LCYC,
         T_EN => T_EN,
         S_EN => S_EN,
         DIV2CK => DIV2CK1,
         CLEAR => CLEAR,
         RST => RST,
         NX1 => NX1,
         NX2 => NX2,
         STATD => STATD(1 downto 1),
         CYC => CYC(2 downto 2),
         TCON => TCON(7 downto 1), 
         RAMDI => RAMDI,
         SFRW => SFRW(13 downto 12)
         );
--*********************************************************************
U12:m3s020bo_e
port map(
         RESINT => RESINT,           
         SP => SP,
         PCON => PCON,
         PSWDAT => PSWDAT,
         MSIZ => MSIZ,
         CO => CO,
         ACO => ACO,
         OV => OV,
         PAR => PAR,
         DAA => DAA,
         MULDIV => MULDIV,
         CJNE => CJNE,
         OPLOAD => OPLOAD,
         INTA => INTA,
         LCYC => LCYC,
         DIV2CK2 => DIV2CK2,
         CLEAR => CLEAR,
         RST => RST,
         STATE12 => STATE12,
         NX1 => NX1,
         NX2 => NX2,
         CYC => CYC(2 downto 1),
         PSWC => PSWC,
         SPC => SPC,
         STATD => STATD(6 downto 1),
         RAMDI => RAMDI,
         SFRW => SFRW(19 downto 16)
         );
--*********************************************************************
U13:m3s023bo_e
port map(
         SFRDAT => SFRDAT,
         FA => LFA(6 downto 0),
         PORTA => PORTA,
         PORTB => PORTB,
         PORTC => PORTC,
         PORTD => PORTD,
         SP => SP,
         DPL => DPL,
         DPH => DPH,
         PCON => PCON,
         TCON => TCON,
         TMOD => TMOD,
         TLA => TLA,
         TLB => TLB,
         THA => THA,
         THB => THB,
         SCON => SCON,
         SBUF => SBUF,
         IE => IE,
         IP => IP,
         PSWDAT => PSWDAT,
         ACCDAT => ACCDAT,
         BREG => BREG,
         MSIZ => MSIZ
         );            
--*********************************************************************
U14:m3s025bo_e
port map(
         OPC => OPC,
         OPLOAD => OPLOAD,
         IROMD => IROMD,
         STATD => STATD(1 downto 1),
         PCON => PCON(0 downto 0),
         CLEAR => CLEAR,
         RST => RST,
         DIV2CK => DIV2CK2,
         NX1 => NX2,
         INTA => INTA,
         LCYC => LCYC,
         DLM => LDLM
         );
--*********************************************************************
U15:m3s028bo_e
port map(
         SCON => SCON,
         SBUF => SBUF,
         RITI => RITI,
         RXDO => RXDO,
         TXDO => TXDO,
         DI => DI(0 downto 0),
         STATE12 => STATE12,
         RAMDI => RAMDI,
         PCON => PCON(7 downto 7),
         SFRW => SFRW(11 downto 10),
         LOV1 => LOV1,
         S_EN => S_EN,
         T_EN => T_EN,
         DIV2CK1 => DIV2CK1,
         NX1 => NX1,
         NX2 => NX2,
         CLEAR => CLEAR
         );
--*********************************************************************
-- Process Definitions
--*********************************************************************
muxoa:process(OAI, IROMD, RAMDI, AI, LDLM)
-- Download mode multiplexer for combinatorial program data read and
-- write paths.
begin
   if LDLM = '0' then
      OA <= OAI;
      FO <= RAMDI;
   else
      OA <= IROMD;
      FO <= AI;
   end if;
end process muxoa;
--*********************************************************************
misc1:process(DIV2CK2, STATD, MOVX, PCADD, IMMB4, LCYC, CYC, LDLM, DI,
              IMMB3, DLMSTQ)
-- Immediate data register write enable and download mode controls.
begin
   IMMDATEN <= DIV2CK2 and ((STATD(3) and MOVX(0))
                          or (STATD(1) and IMMB3 and not LCYC)
                          or (STATD(4) and (CYC(1) or IMMB4)) );
   DLMSTBI <= (DI(6) and DI(7)) or not LDLM;
   DLMR <= LDLM and not DI(7);
   DLMSTB <= DLMSTQ(0) and not DLMSTQ(1) and LDLM;
end process misc1;
--*********************************************************************
muxiromd:process(MD, AI, STATD, MOVX, EXPMEM)
-- Internal/external program memory multiplexer
begin
   if ((STATD(3) and MOVX(0)) or EXPMEM) ='0' then
      IROMD <= MD;
   else
      IROMD <= AI;
   end if;
end process muxiromd;
--*********************************************************************
setclear:process(NX1,RST)
-- Synchronous clear register.
begin
   if RST = '1' then
       CLEAR <= '1';
   elsif NX1'event and NX1 ='1' then
     if (S_EN and (CYC(1) or CLEAR)) = '1' then
       CLEAR <=  '0';
     end if;
   end if;
end process setclear;
--*********************************************************************
setimmdat:process(NX2)
-- Immediate program data register
begin
   if NX2'event and NX2 ='1' then
      if IMMDATEN = '1' then
         IMMDAT <= IROMD;
      end if;
   end if;
end process setimmdat;
--*********************************************************************
setdlmstq:process(NX1)
-- Download mode program counter increment strobe synchroniser
begin
if NX1'event and NX1 ='1' then
      DLMSTQ(0) <= DLMSTBI;
      DLMSTQ(1) <= DLMSTQ(0);
end if;
end process setdlmstq;
--*********************************************************************
direction_ap:process(RST)
-- Bi-direct buffer control for PSEN and ALE signals
begin
  NALEN <= RST;
end process direction_ap;
--*********************************************************************
setdlm:process(NX1)
-- Enter download mode during reset only and at least two clock edges
-- after RST goes high, in order to allow ALE and PSEN to tri-state 
-- first.
begin
if NX1'event and NX1 ='1' then
   LDLM <= RST and not PSEI and not ALEI;
end if;
end process setdlm;
--*********************************************************************
prog_mem_strobes:process(DI,LDLM,MOEI)
-- Internal program memory control outputs.
-- Write strobe (NMWE) may only be active during download mode.
begin
  NMWE <= DI(6) or not LDLM;
  NMOE <= (DI(7) or not LDLM) and (LDLM or not MOEI);
end process prog_mem_strobes;
--*********************************************************************
localout:process(LFA, LDLM, PCON, PROGRAM_ADDR)
-- Rename internal signals for export beyond MegaMacro boundary.
begin
   FA <= LFA;
   DLM <= LDLM;
   XOFF <= PCON(1);
   IDLE <= PCON(0);
   M <= PROGRAM_ADDR;
end process localout;
--*********************************************************************
end m8051_rtl;
--*********************************************************************
