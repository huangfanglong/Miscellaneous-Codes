//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H
//*
//******************************************************************
//*                                                                *
//*  CSCI 465               ASSIGNMENT 6        FALL 2022          *
//*                                                                *
//* PROGRAM NAME: SALESRPT      © 2022 Long F. Huang               *
//* PROGRAMMER:   LONG FANG HUANG                                  *
//* DUE DATE:     11/11/2022                                       *
//*                                                                *
//* FUNCTION:  THIS PROGRAM READS INPUT DATA RECORDS AND THEN      *
//*            WRITES THEM TO STANDARD OUTPUT.                     *
//*                                                                *
//* INPUT:     SALEFLE - THE INPUT DATA RECORDS READ IN.           *
//*                                                                *
//* OUTPUT:    REPORT - THE INPUT DATA RECORDS WRITTEN OUT.        *
//*                                                                *
//* ENTRY CONDITIONS: NONE.                                        *
//*                                                                *
//* EXIT CONDITIONS:  R15 RETURNS A RETURN CODE.                   *
//*                                                                *
//* NOTES: NONE.                                                   *
//*                                                                *
//******************************************************************
//*
//******************************************************************
//*                                                                *
//* JSTEP01 COMPILE THE WRITTEN ASSEMBLER PROGRAM USING HIGH       *
//*         ASSEMBLER                                              *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSLIB   INPUT:  LOAD THE MACRO LIBRARY                        *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN ASSEMBLER PROGRAM       *
//******************************************************************
//JSTEP01 EXEC PGM=ASMA90,PARM=ASA
//SYSLIB   DD  DSN=SYS1.MACLIB,DISP=SHR
//SYSIN    DD   *
         PRINT  NOGEN                MACRO CALL SUPPRESSION
$FUNDREC DSECT                       DSECT FOR FUND RECORD
$ISHRPRC  DS    ZL5                  TABLEIZED SHARE PRICE
$IFUNDNME DS    CL35                 TABLEIZED FUND NAME
$ICOMPCT1 DS    ZL6                  TABLEIZED COMMISSION PERCENT FLAG1
$ICOMPCT2 DS    ZL6                                               FLAG2
$ICOMPCT3 DS    ZL6                                               FLAG3
*
$SALEREC DSECT                       DSECT FOR SALE RECORD
$IBRNCNME DS    CL20                 TABLEIZED BRANCH NAME
$IBRKRNME DS    CL25                 TABLEIZED BROKER NAME
$IDEPAMT  DS    ZL10                 TABLEIZED DEPOSIT AMOUNT
          DS    CL4                  UNUSED 4 BYTES
$ICOMFLG  DS    ZL1                  TABLEIZED COMMISSION PERCENT FLAG
*
SALESRPT CSECT                       BEGIN SALESRPT
*
         STM   14,12,12(13)          SAVE CALLER'S REGS
         LR    12,15                 SET R12 TO R15
         USING SALESRPT,12            ESTABLISH R12 AS 1ST BASE REG
         LA    14,REGS               R14 -> CURRENT SAVE AREA
         ST    13,4(,14)             SAVE CALLER'S SAVE AREA ADDR
         ST    14,8(,14)             SAVE CURRENT SAVE AREA ADDR
         LR    13,14                 R13 -> CURRENT SAVE AREA
*
         LA    11,4095(,12)
         LA    11,1(,11)
         USING SALESRPT+4096,11
*
         TIME  DEC,DATETIME,LINKAGE=SYSTEM,DATETYPE=MMDDYYYY
*
*        MOVING THE DATE IN MM/DD/YYY TO OUTPUT FIELD
*
         MVC   MMDDYYYY-3(13),=X'40202120206120206120202020'
         ED    MMDDYYYY-3(13),DATETIME+7
         MVI   HEADER1,C'1'
*
*        MOVING THE TIME IN HR AND MIN TO TWO OUTPUT FIELDS
*
         MVC   HEADER2-1(7),=X'202120207A2020'
         ED    HEADER2-1(7),DATETIME-1
*
         PACK  TEMPHOUR(2),HEADER2+1(3)
         MVI   TEMPHOUR+1,X'0F'
         SRP   TEMPHOUR(2),64-1,0
*
         CP    TEMPHOUR(2),=PL2'00'
         BNE   HRNOT0
*
         MVC   HEADER2+1(2),=X'F1F2'
         MVC   OAMPM(2),=C'AM'
         B     DONEAMPM
*
HRNOT0   CP    TEMPHOUR(2),=PL2'12'
         BNL   ITISPM
*
         MVC   OAMPM(2),=C'AM'
         B     DONEAMPM
*
ITISPM   MVC   OAMPM(2),=C'PM'
         CP    TEMPHOUR(2),=PL2'13'
         BL    DONEAMPM
*
         SP    TEMPHOUR(2),=PL2'12'
         MVC   HEADER2(3),=X'212020'
         ED    HEADER2(3),TEMPHOUR
*
DONEAMPM MVI   HEADER2,C' '
*
         OPEN  (SALESDCB,(INPUT))  OPEN INPUT FILE
         LTR   15,15               CHECK FOR SUCCESSFUL OPEN
         BZ    OPENOK1             BRANCH IF SUCCESSFUL TO OPENOK1
         ABEND 222,DUMP            ABEND IF OPEN FAILS & DISPLAY 222
*
OPENOK1  OPEN  (RPTDCB,(OUTPUT))   OPEN OUTPUT FILE
         LTR   15,15               CHECK FOR SUCCESSFUL OPEN
         BZ    OPENOK2             BRANCH IF SUCCESSFUL TO OPENOK2
         ABEND 333,DUMP            ABEND IF OPEN FAILS & DISPLAY 333
*
OPENOK2  OPEN  (HSDCB,(OUTPUT))    OPEN OUTPUT FILE
         LTR   15,15               CHECK FOR SUCCESSFUL OPEN
         BZ    OPENOK3             BRANCH IF SUCCESSFUL TO OPENOK3
         ABEND 444,DUMP            ABEND IF OPEN FAILS & DISPLAY 444
*
         USING $FUNDREC,3          EST. ADDRESSABILITY FOR DESECT
*
OPENOK3  GET   SALESDCB            READ FUND RECORD
         LR    3,1                 R3 -> FIRST RECORD
*
         PACK  PSHRPRC(3),$ISHRPRC(5)  SAVE SHARE PRICE INTO STORAGE
*
         LA    1,OSHRPRC+3
         EDMK  OSHRPRC(7),PSHRPRC
         BCTR  1,0
         MVI   0(1),C'$'
*
         MVC   OFUNDNME(35),$IFUNDNME  MOVE FUND NAME TO HEADER
*
         PACK  PCOMPCT1(4),$ICOMPCT1(6) MOVE COMM PERCENT 1 TO STORAGE
         PACK  PCOMPCT2(4),$ICOMPCT2(6) MOVE COMM PERCENT 2 TO STORAGE
         PACK  PCOMPCT3(4),$ICOMPCT3(6) MOVE COMM PERCENT 3 TO STORAGE
*
         DROP  3                       RELEASE ADDRESSABILITY FOR R3
*
         USING $SALEREC,3
*
         LA    2,99                   LINE CTR REG = 99
*
         GET   SALESDCB               READ THE FIRST RECORD
*
LOOP1    CLI   EOFFLAG1,C'Y'          CHECK FOR END OF INPUT DATA
         BE    ENDLOOP1               BRANCH TO ENDLOOP1 IF EOF
*
         LR    3,1
*
         AP    PSALECTR(2),=PL1'1'    ADD 1 TO RECORD COUNTER
*
         MVI   OSALEREC+1,C' '
         MVC   OSALEREC+2(131),OSALEREC+1
*
         MVC   OBRNCNME(20),$IBRNCNME MOVE BRANCH NAME TO DETAIL
         MVC   OBRKRNME(20),$IBRKRNME MOVE BROKER NAME TO DETAIL
*
         PACK  PDEPAMT(6),$IDEPAMT(10) PACK DEPOSIT AMOUNT
*
         LA    1,ODEPAMT+10           PRESET R1
         MVC   ODEPAMT(15),=X'402020206B2020206B2021204B2020'
         EDMK  ODEPAMT(15),PDEPAMT    EDIT DEP AMT INTO DETAIL
         BCTR  1,0                    DECREMENT 1 BY 1
         MVI   0(1),C'$'              PLACE DOLLAR SIGN
*
         AP    PTDEPAMT(7),PDEPAMT    ADD DEP AMT TO TOT DEP AMT
*
         ZAP   PDIVIDE(11),PDEPAMT    COPY DEP AMT TO BIGGER FIELD
         SRP   PDIVIDE(11),4,0        SHIFT ON FOUR DECIMAL PLACES
         DP    PDIVIDE(11),PSHRPRC(3) DIVIDE BY SHR PRC
         SRP   PDIVIDE(8),64-1,5      ROUND OFF FOURTH DEC PLACE
         SRP   PDIVIDE(8),1,0         SHIFT ON FOURTH DEC PLACE 0
*
         MVC   OSHRAMT(20),=X'4020206B2020206B2020206B2021204B20202020'
         ED    OSHRAMT(20),PDIVIDE    EDIT SHR AMT INTO DETAIL
*
         AP    PTSHRAMT(9),PDIVIDE(8) ADD SHR AMT TO TOT SHR AMT
*
         CP    PDIVIDE(8),=PL8'50000.0000'
         BNH   NOTHIGH
*
         MVC   HSBRKNME(25),$IBRKRNME MOVE BROKER NAME TO HS RECORD
         ZAP   HSSHRAMT(8),PDIVIDE(8) COPY SHR AMT TO HS RECORD
*
         PUT   HSDCB,HSREC            WRITE HIGH SALES RECORD
*
NOTHIGH  CLI   $ICOMFLG,C'1'
         BNE   CFLGNOT1
*
         ZAP   PTCOMPCT(4),PCOMPCT1(4)
         B     COMMDONE
*
CFLGNOT1 CLI   $ICOMFLG,C'2'
         BNE   CFLGNOT2
*
         ZAP   PTCOMPCT(4),PCOMPCT2(4)
         B     COMMDONE
*
CFLGNOT2 ZAP   PTCOMPCT(4),PCOMPCT3(4)
*
COMMDONE ZAP   PDIVIDE(11),PDEPAMT(6)
         MP    PDIVIDE(11),PTCOMPCT(4)
         SRP   PDIVIDE(11),64-5,5     SHIFT OFF 5 OF 7 DECIMAL PLACES
*
         LA    1,OCOMAMT+11           PRESET R1
         MVC   OCOMAMT(15),=X'402020206B2020206B2021204B2020'
         EDMK  OCOMAMT(15),PDIVIDE+5  EDIT COM AMT INTO DETAIL
         BCTR  1,0                    DECREMENT 1 BY 1
         MVI   0(1),C'$'              PLACE DOLLAR SIGN
*
         AP    PTCOMAMT(7),PDIVIDE+5(6)  ADD COMM AMT TO TOTAL COMM AMT
*
         C     2,=F'18'               IS IT TIME TO PRINT HEADERS?
         BL    NOHDRS1                BRANCH PAST IF NOT
*
         AP    PPAGECTR(2),=PL1'1'    INCREMENT PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120'
         ED    OPAGECTR(4),PPAGECTR
*
         PUT   RPTDCB                 PRINT FIRST HEADER
         MVC   0(133,1),HEADER1
         PUT   RPTDCB                 PRINT SUBHEADER
         MVC   0(133,1),HEADER2
         PUT   RPTDCB                 PRINT SHARE PRICE LINE
         MVC   0(133,1),HEADER3
         PUT   RPTDCB                 PRINT COLUMN HEADER
         MVC   0(133,1),COLHDR1
         PUT   RPTDCB                 PRINT HYPHEN LINE
         MVC   0(133,1),HYPHENS1
*
         SR    2,2                    ZERO OUT LINE COUNTER
*
NOHDRS1  PUT   RPTDCB                 WRITE THE PRINT DATA
         MVC   0(133,1),OSALEREC
         LA    2,1(,2)                INCREMENT LINE COUNTER
*
         GET   SALESDCB               GET THE NEXT RECORD
*
         B     LOOP1                  BRANCH TO TOP OF LOOP1
*
         DROP  3
*
ENDLOOP1 AP    PPAGECTR(2),=PL1'1'    INCREMENT PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120'
         ED    OPAGECTR(4),PPAGECTR
*
         PUT   RPTDCB                 PRINT FIRST HEADER
         MVC   0(133,1),HEADER1
         MVC   OSUBHDR2(29),=C'BROKER SALES AND COMMISSIONS '
         MVC   OSUBHDR2+29(13),=C'REPORT TOTALS'
         PUT   RPTDCB                 PRINT SUBHEADER
         MVC   0(133,1),HEADER2
         PUT   RPTDCB                 PRINT SHARE PRICE LINE
         MVC   0(133,1),HEADER3
         PUT   RPTDCB                 PRINT COLUMN HEADER 2
         MVC   0(133,1),COLHDR2
         PUT   RPTDCB                 PRINT HYPHEN LINE 2
         MVC   0(133,1),HYPHENS2
*
         MVC   OSALECTR(4),=X'40202120'
         ED    OSALECTR(4),PSALECTR
*
         LA    1,OTDEPAMT+14
         EDMK  OTDEPAMT(18),PTDEPAMT
         BCTR  1,0
         MVI   0(1),C'$'
*
         ED    OTSHRAMT(23),PTSHRAMT
*
         LA    1,OTCOMAMT+14
         EDMK  OTCOMAMT(18),PTCOMAMT
         BCTR  1,0
         MVI   0(1),C'$'
*
         PUT   RPTDCB
         MVC   0(133,1),TOTALS1
*
         CLOSE (SALESDCB,,HSDCB)  CLOSE THE TWO DCBS
*
         OPEN  (HSDCB,(INPUT))     OPEN INPUT HS FILE
         LTR   15,15               CHECK FOR SUCCESSFUL OPEN
         BZ    OPENOK4             BRANCH IF SUCCESSFUL TO OPENOK3
         ABEND 777,DUMP            ABEND IF OPEN FAILS & DISPLAY 777
*
OPENOK4  LA    2,99                RESET LINE COUNTER
*
         ZAP   PSALECTR(2),=PL1'0' ZERO OUT HS COUNTER
         ZAP   PPAGECTR(2),=PL1'0' ZERO OUT PAGE COUNTER
         ZAP   PTSHRAMT(9),=PL1'0' ZERO OUT TOTAL SHR AMT
*
         MVC   OSUBHDR2(21),=C'        BROKER LARGE '
         MVC   OSUBHDR2+21(21),=C'SALES REPORT         '
*
         GET   HSDCB,HSREC
*
LOOP2    CLI   EOFFLAG2,C'Y'
         BE    ENDLOOP2
*
         AP    PSALECTR(2),=PL1'1' ADD 1 TO HS COUNTER
*
         MVC   OHBRKNME(25),HSBRKNME
*
         MVC  OHSHRAMT(20),=X'4020206B2020206B2020206B2021204B20202020'
         ED    OHSHRAMT(20),HSSHRAMT    EDIT SHR AMT INTO DETAIL
*
         AP    PTSHRAMT(9),HSSHRAMT(8)
*
         C     2,=F'18'               IS IT TIME TO PRINT HEADERS?
         BL    NOHDRS2                BRANCH PAST IF NOT
*
         AP    PPAGECTR(2),=PL1'1'    INCREMENT PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120'
         ED    OPAGECTR(4),PPAGECTR
*
         PUT   RPTDCB                 PRINT FIRST HEADER
         MVC   0(133,1),HEADER1
         PUT   RPTDCB                 PRINT SUBHEADER
         MVC   0(133,1),HEADER2
         PUT   RPTDCB                 PRINT SHARE PRICE LINE
         MVC   0(133,1),HEADER3
         PUT   RPTDCB                 PRINT COLUMN HEADER
         MVC   0(133,1),COLHDR3
         PUT   RPTDCB                 PRINT HYPHEN LINE
         MVC   0(133,1),HYPHENS3
*
         SR    2,2                    ZERO OUT LINE COUNTER
*
NOHDRS2  PUT   RPTDCB                 PRINT HIGH SALES REC
         MVC   0(133,1),OHSREC
         LA    2,1(,2)                INCREMENT LINE COUNTER
*
         GET   HSDCB,HSREC
*
         B     LOOP2
*
ENDLOOP2 AP    PPAGECTR(2),=PL1'1'    INCREMENT PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120'
         ED    OPAGECTR(4),PPAGECTR
*
         MVC   OSUBHDR2(24),=C'     BROKER LARGE SALES '
         MVC   OSUBHDR2+24(18),=C'REPORT TOTALS     '
*
         PUT   RPTDCB                 PRINT FIRST HEADER
         MVC   0(133,1),HEADER1
         PUT   RPTDCB                 PRINT SUBHEADER
         MVC   0(133,1),HEADER2
         PUT   RPTDCB                 PRINT SHARE PRICE LINE
         MVC   0(133,1),HEADER3
         PUT   RPTDCB                 PRINT COLUMN HEADER
         MVC   0(133,1),COLHDR4
         PUT   RPTDCB                 PRINT HYPHEN LINE
         MVC   0(133,1),HYPHENS4
*
         MVC   OHSCTR(4),=X'40202120'
         ED    OHSCTR(4),PSALECTR
*
         ED    OHSTSHRS(23),PTSHRAMT
*
         PUT   RPTDCB
         MVC   0(133,1),TOTALS2
*
         CLOSE (HSDCB,,RPTDCB)
*
         SR    15,15
         L     13,4(,13)
         L     14,12(,13)
         LM    0,12,20(13)
         BR    14
*
         LTORG
         ORG   SALESRPT+((*-SALESRPT+31)/32)*32
         DC    C'HERE IS THE STORAGE: SALESRPT **'
*
REGS     DC    18F'0'
*
PSALECTR DC    PL2'0'
PPAGECTR DC    PL2'0'
PSHRPRC  DC    PL3'0'
PCOMPCT1 DC    PL4'0'
PCOMPCT2 DC    PL4'0'
PCOMPCT3 DC    PL4'0'
PTCOMPCT DC    PL4'0'
PDEPAMT  DC    PL6'0'
PTDEPAMT DC    PL7'0'
PSHRAMT  DC    PL8'0'
PTSHRAMT DC    PL9'0'
PCOMMAMT DC    PL6'0'
PTCOMAMT DC    PL7'0'
PDIVIDE  DC    PL11'0'
TEMPHOUR DC    PL2'0'
*
HSREC    DS    0H
HSBRKNME DS    CL25
HSSHRAMT DS    PL8
*
OSALEREC DC    C'0'
OBRNCNME DS    CL25
         DC    8C' '
OBRKRNME DS    CL25
         DC    8C' '
ODEPAMT  DS    CL15
         DC    7C' '
OSHRAMT  DS    CL20
         DC    9C' '
OCOMAMT  DS    CL15
*
OHSREC   DC    C'0'
         DC    37C' '
OHBRKNME DS    CL25
         DC    13C' '
OHSHRAMT DS    CL20
         DC    37C' '
*
TOTALS1  DC    C'0'
         DC    50C' '
OSALECTR DC    X'40202120'   4
         DC    9C' '
OTDEPAMT DC    X'4020206B2020206B2020206B2021204B2020'   18
         DC    4C' '
OTSHRAMT DC    X'40206B2020206B2020206B2020206B2021204B20202020'   23
         DC    6C' '
OTCOMAMT DC    X'4020206B2020206B2020206B2021204B2020'   18
*
TOTALS2  DC    C'0'
         DC    58C' '
OHSCTR   DS    CL4
         DC    10C' '
OHSTSHRS DC    X'40206B2020206B2020206B2020206B2021204B20202020'   23
         DC    37C' '
*
         DS    CL1
HEADER1  DC    C'1'
MMDDYYYY DS    CL10
         DC    39C' '
OFUNDNME DS    CL35
         DC    39C' '
         DC    C'PAGE:'
OPAGECTR DS    CL4
*
         DS    CL1
HEADER2  DC    C' '
HHMM1    DS    CL5
         DC    C' '
OAMPM    DS    CL2
         DC    37C' '
OSUBHDR2 DC    C'   BROKER SALES AND COMMISSIONS REPORT    '   42
         DC    45C' '
*
HEADER3  DC    C'0'
         DC    56C' '
         DC    C'SHARE PRICE: '         13
OSHRPRC  DC    X'402021204B2020'
         DC    56C' '
*
COLHDR1  DC    C'0'
         DC    C'BRANCH NAME'
         DC    22C' '
         DC    C'BROKER NAME'
         DC    25C' '
         DC    C'SALES AMOUNT'
         DC    15C' '
         DC    C'SHARE AMOUNT'
         DC    14C' '
         DC    C'COMMISSION'
*
COLHDR2  DC    C'0'
         DC    39C' '
         DC    C'NUMBER OF SALES'
         DC    9C' '
         DC    C'TOTAL SALES AMOUNT'
         DC    9C' '
         DC    C'TOTAL SHARE AMOUNT'
         DC    8C' '
         DC    C'TOTAL COMMISSION'
*
COLHDR3  DC    C'0'
         DC    37C' '
         DC    C'HIGH SALES BROKER NAME'
         DC    13C' '
         DC    C'HIGH SALES SHARE AMOUNT'
         DC    37C' '
*
COLHDR4  DC    C'0'
         DC    34C' '
         DC    C'NUMBER OF HIGH SALES BROKERS'   28
         DC    4C' '
         DC    C'TOTAL HIGH SALES SHARE AMOUNT'  29
         DC    37C' '
*
HYPHENS1 DC    C' '
         DC    C'-------------------------'
         DC    8C' '
         DC    C'-------------------------'
         DC    8C' '
         DC    C'---------------'
         DC    7C' '
         DC    C'--------------------'
         DC    9C' '
         DC    C'---------------'
*
HYPHENS2 DC    C' '
         DC    39C' '
         DC    C'---------------'
         DC    9C' '
         DC    C'------------------'
         DC    4C' '
         DC    C'-----------------------'
         DC    6C' '
         DC    C'------------------'
*
HYPHENS3 DC    C' '
         DC    37C' '
         DC    C'-------------------------'
         DC    10C' '
         DC    C'-----------------------'
         DC    37C' '
*
HYPHENS4 DC    C' '
         DC    34C' '
         DC    C'----------------------------'
         DC    4C' '
         DC    C'-----------------------------'
         DC    40C' '
*
         DC    XL1'00'
DATETIME DC    4F'0'
*
SALESDCB  DCB  DDNAME=SALEFLE,                                         X
               DEVD=DA,                                                X
               DSORG=PS,                                               X
               MACRF=GL,                                               X
               RECFM=FB,                                               X
               LRECL=80,                                               X
               EODAD=EOFRTN1
*
EOFFLAG1 DC    C'N'                  EOFFLAG FOR INPUT FILE
*
EOFRTN1  MVI   EOFFLAG1,C'Y'         SET EOF FLAG TO Y
         BR    14                    BRANCH TO STMT FOLLOWING GET
*
RPTDCB   DCB   DDNAME=RPTFLE,                                          X
               DEVD=DA,                                                X
               DSORG=PS,                                               X
               MACRF=PL,                                               X
               RECFM=FBA,                                              X
               LRECL=133,                                              X
               BLKSIZE=133
*
HSDCB    DCB   DDNAME=TEMPFLE,                                         X
               DEVD=DA,                                                X
               DSORG=PS,                                               X
               MACRF=(GM,PM),                                          X
               RECFM=FB,                                               X
               LRECL=33,                                               X
               BLKSIZE=330,                                            X
               EODAD=EOFRTN2
*
EOFFLAG2 DC    C'N'                  EOFFLAG FOR INPUT FILE
*
EOFRTN2  MVI   EOFFLAG2,C'Y'         SET EOF FLAG TO Y
         BR    14                    BRANCH TO STMT FOLLOWING GET
*
         END   SALESRPT
//*
//******************************************************************
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSLIN   OUTPUT: WRITE OBJ MODULE TO TEMP DATA SET &&OBJMOD    *
//*                                                                *
//* SYSPRINT OUTPUT: WRITES DATA SET TO STANDARD OUTPUT            *
//*                                                                *
//******************************************************************
//*
//SYSLIN   DD  DSN=&&OBJMOD,SPACE=(CYL,(1,1)),
//             DISP=(MOD,PASS,DELETE)
//*
//SYSPRINT DD  SYSOUT=*
//*
//SYSUT1   DD  SPACE=(CYL,(1,1))
//SYSUT2   DD  SPACE=(CYL,(1,1))
//SYSUT3   DD  SPACE=(CYL,(1,1))
//SYSUT4   DD  SPACE=(CYL,(1,1))
//SYSUT5   DD  SPACE=(CYL,(1,1))
//SYSUT6   DD  SPACE=(CYL,(1,1))
//SYSUT7   DD  SPACE=(CYL,(1,1))
//SYSUT8   DD  SPACE=(CYL,(1,1))
//SYSUT9   DD  SPACE=(CYL,(1,1))
//SYSUT10  DD  SPACE=(CYL,(1,1))
//SYSUT11  DD  SPACE=(CYL,(1,1))
//SYSUT12  DD  SPACE=(CYL,(1,1))
//SYSUT13  DD  SPACE=(CYL,(1,1))
//SYSUT14  DD  SPACE=(CYL,(1,1))
//SYSUT15  DD  SPACE=(CYL,(1,1))
//*
//******************************************************************
//*                                                                *
//* JSTEP02 BINDS THE PROGRAM AND PRODUCE A PROGRAM OBJECT         *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN SALESRPT PROGRAM        *
//*                                                                *
//* SYSLIB   INPUT:  LOADS IBM LANGUAGE ENVIRONMENT DATA SET       *
//*                                                                *
//* SYSLIN   INPUT:  LOADS THE TEMP &&OBJMOD                       *
//*                                                                *
//* SYSLMOD  OUTPUT: LOAD THE MODULE CREATED BY THE BINDER INTO    *
//*                  STUDENT'S LOADLIB                             *
//*                                                                *
//* SYSPRINT OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP02  EXEC PGM=HEWL,COND=(0,LT)
//SYSLIB   DD  DSN=CEE.SCEELKED,DISP=SHR
//SYSLIN   DD  DSN=&&OBJMOD,DISP=(OLD,DELETE)
//*
//SYSLMOD  DD  DSN=KC03E6A.CSCI465.LOADLIB(SALESRPT),
//             SPACE=(1024,(50,20,1)),DSNTYPE=LIBRARY,
//             DISP=(MOD,KEEP,KEEP)
//*
//SYSPRINT DD  SYSOUT=*
//*
//******************************************************************
//*                                                                *
//* JSTEP03 FETCH THE PROGRAM                                      *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  LOAD FROM STUDENT LIBRARY                     *
//*                                                                *
//* SALEFLE INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE            *
//*                                                                *
//* RPTFLE  OUTPUT: OUTPUT FOR THE SALESRPT PROGRAM WRITTEN TO     *
//*                  STANDARD OUTPUT                               *
//*                                                                *
//*                                                                *
//* PRINTOUT OUTPUT: PRINT TO STANDARD OUTPUT                      *
//*                                                                *
//* SYSUDUMP OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP03 EXEC PGM=SALESRPT,COND=(0,LT)
//STEPLIB  DD  DSN=KC03E6A.CSCI465.LOADLIB,DISP=SHR
//SALEFLE  DD  DSN=KC02322.CSCI465.ASNDATA(ASN6DATA),DISP=SHR
//RPTFLE   DD  SYSOUT=*
//TEMPFLE  DD  SPACE=(TRK,(1,1))
//SYSUDUMP DD  SYSOUT=*
//
