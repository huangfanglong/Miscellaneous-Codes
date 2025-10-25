//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H,REGION=0M
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 7        FALL 2022         *
//*                                                               *
//* PROGRAM NAME: COBOL 3  	  © 2022 Long F. Huang                *
//* PROGRAMMER:   LONG FANG HUANG                                 *
//* DUE DATE:     12/02/2022                                      *
//*                                                               *
//* FUNCTION: THIS PROGRAM READS INPUT DATA RECORDS               *
//*            AND THEN WRITES THEM TO STANDARD OUTPUT.           *
//*                                                               *
//* INPUT: SALESFLE - THE INPUT DATA RECORDS READ IN.             *
//*                                                               *
//* OUTPUT: OUTDATA - THE INPUT DATA RECORDS WRITTEN              *
//*                    OUT.                                       *
//*                                                               *
//* NOTES: NONE                                                   *
//*****************************************************************
//*
//******************************************************************
//*                                                                *
//* JSTEP01  SORT THE PDSE MEMBER 'FUNDS'                          *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SORTIN   INPUT:  INDICATES WHERE DATA SET FROM COBALT          *
//*                  COMPILER IS STORED                            *
//* SORTOUT  OUTPUT: INDICATES THE SORTED DATA SET                 *
//*                                                                *
//******************************************************************
//JSTEP01  EXEC PGM=SORT,PARM='CMP=CLC'
//*
//SORTIN   DD DSN=KC02322.CSCI465.ASNDATA(FUNDS),DISP=SHR
//SORTOUT  DD DSN=&&SORTED,SPACE=(TRK,(1,5)),DISP=(NEW,PASS)
//*
//SYSOUT   DD SYSOUT=*
//*
//SYSIN    DD *
  SORT FIELDS=(1,3,ZD,A)
/*
//*
//******************************************************************
//*                                                                *
//* JSTEP02 COMPILE THE WRITTEN COBALT PROGRAMUSING COBALT COMPILER*
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  INDICATES WHERE DATA SET FROM COBALT          *
//*                  COMPILER IS STORED                            *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
//*                                                                *
//* SYSLIN   OUTPUT: WRITE OBJ MODULE TO TEMP DATA SET &&OBJMOD    *
//*                                                                *
//* SYSPRINT OUTPUT: WRITES DATA SET TO STANDARD OUTPUT            *
//*                                                                *
//******************************************************************
//JSTEP02  EXEC PGM=IGYCRCTL,PARM=APOST
//STEPLIB  DD   DSN=IGY630.SIGYCOMP,DISP=SHR
//         DD   DSN=CEE.SCEERUN,DISP=SHR
//         DD   DSN=CEE.SCEERUN2,DISP=SHR
//SYSLIB   DD   DSN=KC02322.CSCI465.COPYLIB,DISP=SHR
//SYSIN    DD   *

       IDENTIFICATION DIVISION.

       PROGRAM-ID.    SALESRPT.
       AUTHOR.        GEOFFREY D DECKER.
       DATE-WRITTEN.  09/10/2022.
       DATE-COMPILED.

       ENVIRONMENT DIVISION.

       INPUT-OUTPUT SECTION.

       FILE-CONTROL.

           SELECT SALES-FILE ASSIGN TO SALESFLE.
           SELECT FUND-FILE ASSIGN TO FUNDFLE.
           SELECT REPORT-FILE ASSIGN TO RPTFLE.
           SELECT TEMP-FILE ASSIGN TO TEMPFLE.

       DATA DIVISION.

       FILE SECTION.

       FD  SALES-FILE
           RECORDING MODE F.

       01  SALE-RECORD.
           05  SALE-BRANCH-NME      PIC X(20).
           05  SALE-BROKER-NME      PIC X(25).
           05  SALE-DETAIL          OCCURS 4
                                    INDEXED BY SALE-NDX.
               10  SALE-FUND-NBR    PIC 9(3).
               10  SALE-SHR-PRC-FLG PIC 9.
               10  SALE-DEP-AMT     PIC S9(8)V99.

       FD  FUND-FILE
           RECORDING MODE F.

       01  FUND-RECORD.
           05  IN-FUND-NBR          PIC 9(3).
           05  IN-FUND-NME          PIC X(25).
           05  IN-FUND-COMM-PCT     PIC S9(3)V9(3).

       FD  REPORT-FILE
           RECORDING MODE F
           BLOCK CONTAINS 20 RECORDS.

       01  REPORT-RECORD            PIC X(132).

       FD  TEMP-FILE
           RECORDING MODE F.

       01  TEMP-RECORD.
           05  HS-BROKER-NME        PIC X(25).
           05  HS-FUND-NBR          PIC S9(3)       PACKED-DECIMAL.
           05  HS-SHR-AMT           PIC S9(14)V9(4) PACKED-DECIMAL.

       WORKING-STORAGE SECTION.

       01  FUND-TBL.
           05  TBL-FUND-CTR          PIC S9(3)  BINARY SYNC VALUE 0.
           05  TBL-FUND-NTRY         OCCURS 1 TO 199
                                     DEPENDING ON TBL-FUND-CTR
                                     ASCENDING KEY TBL-FUND-NBR
                                     INDEXED BY TBL-FUND-NDX.
       COPY FUNDTBL.

       01  SUBPROGRAM              PIC X(8) VALUE 'BUILDTBL'.
       01  CALCSHR                 PIC X(8) VALUE 'CALCSHR'.
       01  HISALES                 PIC X(8) VALUE 'HISALES'.
       01  JOBNAME                 PIC X(8) VALUE 'JOBNAME'.

       01  EOF-FLAG                 PIC X     VALUE 'N'.
       01  EOF-FLAG2                PIC X     VALUE 'N'.

       01  COUNTERS.
           05  RECORD-CTR           PIC S9(3) BINARY SYNC VALUE 0.
           05  BROKER-CTR           PIC S9(3) PACKED-DECIMAL VALUE 0.
           05  LINE-CTR             PIC S9(2) BINARY SYNC VALUE 99.
           05  PAGE-CTR             PIC S9(3) PACKED-DECIMAL VALUE 0.
           05  HS-CTR               PIC S9(3) BINARY SYNC VALUE 0.

       01  TOTALS.
           05  TOT-DEP-AMT          PIC S9(12)V99
                                       PACKED-DECIMAL VALUE 0.
           05  TOT-SHR-AMT          PIC S9(14)V9999
                                       PACKED-DECIMAL VALUE 0.
           05  TOT-COMM-AMT         PIC S9(12)V99
                                       PACKED-DECIMAL VALUE 0.

       01  HIGH-SALE-RECORD.
           05  IN-HS-BROKER-NME     PIC X(25).
           05  IN-HS-FUND-NBR       PIC S9(3) PACKED-DECIMAL.
           05  IN-HS-SHR-AMT        PIC S9(14)V9999
                                       PACKED-DECIMAL VALUE 0.

       01  VARIABLES.
           05  DEP-AMT              PIC S9(8)V99
                                       PACKED-DECIMAL VALUE 0.
           05  AVG-DEP-AMT          PIC S9(8)V99
                                       PACKED-DECIMAL VALUE 0.
           05  SHR-AMT              PIC S9(10)V9999
                                       PACKED-DECIMAL VALUE 0.
           05  COMM-PCT             PIC S9V9(5)
                                       PACKED-DECIMAL VALUE 0.
           05  SHR-PRC              PIC S9(3)V9(2)
                                       PACKED-DECIMAL VALUE 0.
           05  TOT-HS-SHR-AMT       PIC S9(14)V9999
                                       PACKED-DECIMAL VALUE 0.

       01  HEADER-1.
           05  HEADER-DATE.
               10  CURRENT-MONTH    PIC 9(2).
               10                   PIC X VALUE '/'.
               10  CURRENT-DAY      PIC 9(2).
               10                   PIC X VALUE '/'.
               10  CURRENT-YEAR     PIC 9(4).
           05                       PIC X(40) VALUE SPACES.
           05                       PIC X(32)
                              VALUE 'WASHINGTON & LINCOLN INVESTMENTS'.
           05                       PIC X(41) VALUE SPACES.
           05                       PIC X(6) VALUE 'PAGE: '.
           05  OUT-PAGE-CTR         PIC ZZ9.

       01  HEADER-2.
           05  HEADER-TIME.
               10  HOUR             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM             PIC X(2).
           05                       PIC X(44) VALUE SPACES.
           05                       PIC X(27)
                          VALUE 'BROKER DAILY DEPOSIT REPORT'.
           05                       PIC X(36) VALUE SPACES.
           05                       PIC X(9) VALUE 'JOBNAME: '.
           05  JOBNME               PIC X(8).

       01  HEADER-3.
           05                       PIC X(89) VALUE SPACES.
           05                       PIC X(7)  VALUE 'DEPOSIT'.
           05                       PIC X(26) VALUE SPACES.
           05                       PIC X(10) VALUE 'COMMISSION'.

       01  HEADER-4.
           05                       PIC X(20)
                             VALUE 'BRANCH NAME         '.
           05                       PIC X(3) VALUE SPACES.
           05                       PIC X(25)
                             VALUE 'BROKER NAME              '.
           05                       PIC X(1) VALUE SPACES.
           05                       PIC X(4) VALUE 'FUND'.
           05                       PIC X(2) VALUE SPACES.
           05                       PIC X(25)
                             VALUE 'FUND NAME                '.
           05                       PIC X(1) VALUE SPACES.
           05                       PIC X(15)
                             VALUE '         AMOUNT'.
           05                       PIC X(2) VALUE SPACES.
           05                       PIC X(18)
                             VALUE '       SHARES SOLD'.
           05                       PIC X(1) VALUE SPACES.
           05                       PIC X(15) VALUE '         AMOUNT'.

       01  HEADER-5.
           05                       PIC X(20) VALUE ALL '-'.
           05                       PIC X(3)  VALUE SPACES.
           05                       PIC X(25) VALUE ALL '-'.
           05                       PIC X(1)  VALUE SPACES.
           05                       PIC X(4)  VALUE ALL '-'.
           05                       PIC X(2)  VALUE SPACES.
           05                       PIC X(25) VALUE ALL '-'.
           05                       PIC X(1)  VALUE SPACES.
           05                       PIC X(15) VALUE ALL '-'.
           05                       PIC X(2)  VALUE SPACES.
           05                       PIC X(18) VALUE ALL '-'.
           05                       PIC X(1)  VALUE SPACES.
           05                       PIC X(15) VALUE ALL '-'.

       01  DETAIL-LINE.
           05  OUT-BRANCH-NME       PIC X(20).
           05                       PIC X(3) VALUE SPACES.
           05  OUT-BROKER-NME       PIC X(25).
           05                       PIC X(1) VALUE SPACES.
           05  OUT-FUND-NBR         PIC ZZZ9.
           05                       PIC X(2) VALUE SPACES.
           05  OUT-FUND-NME         PIC X(25).
           05                       PIC X(2) VALUE SPACES.
           05  OUT-DEP-AMT          PIC $$$,$$$,$$9.99.
           05                       PIC X(4) VALUE SPACES.
           05  OUT-SHR-AMT          PIC ZZZ,ZZZ,ZZ9.9990.
           05                       PIC X(2) VALUE SPACES.
           05  OUT-COMM-AMT         PIC $$$,$$$,$$9.99.

       01  HEADER-TOTALS.
           05  HEADER-TIME.
               10  HOUR2             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE2           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM2             PIC X(2).
           05                       PIC X(44) VALUE SPACES.
           05                       PIC X(27)
                    VALUE 'BROKER DAILY DEPOSIT REPORT'.
           05                       PIC X(36) VALUE SPACES.
           05                       PIC X(9) VALUE 'JOBNAME: '.
           05  JOBNME2              PIC X(8).

       01  HEADER-TOTALS2.
           05                       PIC X(43) VALUE SPACES.
           05                       PIC X(46)
               VALUE '***** BROKER DAILY DEPOSIT REPORT TOTALS *****'.
           05                       PIC X(43) VALUE SPACES.

       01  HEADER-TOTALS3.
           05                       PIC X(23) VALUE SPACES.
           05                       PIC X(7)  VALUE 'BROKERS'.
           05                       PIC X(11) VALUE SPACES.
           05                       PIC X(15) VALUE 'NUMBER OF SALES'.
           05                       PIC X(22) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE '    TOTAL DEPOSITS'.
           05                       PIC X(18) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE ' TOTAL COMMISSIONS'.

       01  HEADER-TOTALS4.
           05                       PIC X(23) VALUE SPACES.
           05                       PIC X(7)  VALUE ALL '-'.
           05                       PIC X(11) VALUE SPACES.
           05                       PIC X(15) VALUE ALL '-'.
           05                       PIC X(22) VALUE SPACES.
           05                       PIC X(18) VALUE ALL '-'.
           05                       PIC X(18) VALUE SPACES.
           05                       PIC X(18) VALUE ALL '-'.

       01  TOTALS-LINE.
           05                       PIC X(27) VALUE SPACES.
           05  OUT-BROKER-CTR       PIC ZZ9.
           05                       PIC X(23) VALUE SPACES.
           05  OUT-SALE-REC         PIC ZZ9.
           05                       PIC X(22) VALUE SPACES.
           05  OUT-TOT-DEP-AMT      PIC $$$,$$$,$$$,$$9.99.
           05                       PIC X(18) VALUE SPACES.
           05  OUT-TOT-COMM-AMT     PIC $$$,$$$,$$$,$$9.99.

       01  AVERAGE-LINE.
           05                       PIC X(50) VALUE SPACES.
           05                       PIC X(27)
                             VALUE 'AVERAGE DEPOSIT BY BROKER: '.
           05  OUT-AVG-DEP          PIC $$$,$$$,$$$,$$9.99.
           05                       PIC X(37) VALUE SPACES.

       01  CURRENT-DATE-FIELDS.
           05  CURRENT-DATE.
               10  CURRENT-YEAR     PIC 9(4).
               10  CURRENT-MONTH    PIC 9(2).
               10  CURRENT-DAY      PIC 9(2).
           05  CURRENT-TIME.
               10  CURRENT-HOUR     PIC 9(2).
               10  CURRENT-MINUTE   PIC 9(2).
               10  CURRENT-SECOND   PIC 9(2).
               10  CURRENT-MS       PIC 9(2).
           05  DIFF-FROM-GMT        PIC S9(4).

       PROCEDURE DIVISION.

       0000-MAIN.

           CALL JOBNAME USING JOBNAME.
           MOVE JOBNAME TO JOBNME.
           MOVE JOBNAME TO JOBNME2.

           CALL SUBPROGRAM USING FUND-TBL
                                 EOF-FLAG.

           PERFORM 0100-DATE-TIME.

           OPEN INPUT  SALES-FILE
                OUTPUT TEMP-FILE
                OUTPUT REPORT-FILE.

           READ SALES-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

           PERFORM 0101-PROCESS-ENTRIES
            VARYING TBL-FUND-NDX FROM 1 BY 1
             UNTIL TBL-FUND-NDX > 198
                OR EOF-FLAG = 'Y'.

           PERFORM 0130-WRITE-TOTALS.

           CALL 'HISALES'.

           MOVE 0 TO RETURN-CODE.

           STOP RUN.

           CLOSE TEMP-FILE
                 REPORT-FILE
                 SALES-FILE.

       0000-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE CALL THE DATE-TIME FUNCTION AND CHANGE IT  *
      * TO 12 HOUR FORMAT CLOCK.                                   *
      *                                                            *
      **************************************************************

       0100-DATE-TIME.

           MOVE FUNCTION CURRENT-DATE TO CURRENT-DATE-FIELDS.
           MOVE CORRESPONDING CURRENT-DATE TO HEADER-DATE.

           MOVE CURRENT-HOUR TO   HOUR
                                  HOUR2.

           MOVE CURRENT-MINUTE TO MINUTE
                                  MINUTE2.

           IF HOUR > 12
               MOVE 'PM' TO AMPM
               COMPUTE HOUR = HOUR - 12

           ELSE
               MOVE 'AM' TO AMPM
           END-IF.

           IF HOUR2 > 12
               MOVE 'PM' TO AMPM2
               COMPUTE HOUR2 = HOUR2 - 12

           ELSE
               MOVE 'AM' TO AMPM2
           END-IF.

      **************************************************************
      * THIS SUBROUTINE PROCESSES THE ENTIRE RECORD, COMPUTE TOTAL *
      * AMOUNT OF DEPOSIT.                                         *
      *                                                            *
      **************************************************************

       0100-PROCESS-RECORD.

           IF SALE-NDX = 1
               MOVE SALE-BRANCH-NME TO OUT-BRANCH-NME
               MOVE SALE-BROKER-NME TO OUT-BROKER-NME
           ELSE
               MOVE SPACES TO OUT-BRANCH-NME
               MOVE SPACES TO OUT-BROKER-NME
           END-IF.

           MOVE SALE-FUND-NBR (SALE-NDX) TO OUT-FUND-NBR.
           MOVE SALE-DEP-AMT (SALE-NDX) TO OUT-DEP-AMT.

           SEARCH ALL TBL-FUND-NTRY
               AT END
                   PERFORM 0180-NBR-NOT-FOUND
               WHEN TBL-FUND-NBR(TBL-FUND-NDX) = SALE-FUND-NBR(SALE-NDX)
                   PERFORM 0190-NBR-FOUND
           END-SEARCH.

           COMPUTE TOT-SHR-AMT ROUNDED = SHR-AMT + TOT-SHR-AMT.

           IF LINE-CTR > 17
               PERFORM 0110-WRITE-HEADERS
           END-IF.

           WRITE REPORT-RECORD FROM DETAIL-LINE AFTER 2.

           ADD 1 TO LINE-CTR.
           ADD 1 TO RECORD-CTR.

       0100-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE PROCESSES THE PROCESS RECORD               *
      *            (PROCESS-CEPTION?)                              *
      *                                                            *
      **************************************************************

       0101-PROCESS-ENTRIES.

           PERFORM 0100-PROCESS-RECORD VARYING SALE-NDX FROM 1 BY 1
            UNTIL SALE-NDX > 4
               OR SALE-FUND-NBR (SALE-NDX) = 0.

           ADD 1 TO BROKER-CTR.

           READ SALES-FILE
               AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0101-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE TALLIES PAGE NUMBER AND PRINT THE HEADER   *
      *                                                            *
      **************************************************************

       0110-WRITE-HEADERS.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-2 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-4 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-5 AFTER 1.

           MOVE 0 TO LINE-CTR.

       0110-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE CALCULATES COMMISSION AND PROCESS HIGH SALE*
      * BROKERS (>50,000 SHARES) TO TEMP DATA SET BY CALLING       *
      * 01400-ADD-TO-TEMP-FILE SUBROUTINE.                         *
      *                                                            *
      **************************************************************

       0120-COMPUTE-COMMISSION-AMT.

           IF SHR-AMT > 10000.0000
               PERFORM 0140-ADD-TO-TEMP-FILE
           END-IF.

           COMPUTE OUT-COMM-AMT ROUNDED =
                COMM-PCT * DEP-AMT / 100.

           COMPUTE TOT-COMM-AMT ROUNDED =
                (COMM-PCT * DEP-AMT / 100) + TOT-COMM-AMT.

       0120-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE PRINTS THE TOTALED AMOUNT OF RELEVANT DATA *
      *                                                            *
      **************************************************************

       0130-WRITE-TOTALS.

           MOVE IN-FUND-NME TO OUT-FUND-NME.
           MOVE TOT-COMM-AMT TO OUT-TOT-COMM-AMT.
           MOVE TOT-DEP-AMT TO OUT-TOT-DEP-AMT.
           MOVE RECORD-CTR TO OUT-SALE-REC.
           MOVE BROKER-CTR TO OUT-BROKER-CTR.

           COMPUTE AVG-DEP-AMT ROUNDED = TOT-DEP-AMT / BROKER-CTR.
           MOVE AVG-DEP-AMT TO OUT-AVG-DEP.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-TOTALS AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-TOTALS2 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-TOTALS3 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-TOTALS4 AFTER 1.
           WRITE REPORT-RECORD FROM TOTALS-LINE AFTER 1.
           WRITE REPORT-RECORD FROM AVERAGE-LINE AFTER 2.

           MOVE 0 TO LINE-CTR.

       0130-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE MOVE THE SELECTED DATA INTO A TEMPORARY    *
      * DATA SET.                                                  *
      *                                                            *
      **************************************************************

       0140-ADD-TO-TEMP-FILE.

           MOVE SALE-BROKER-NME TO IN-HS-BROKER-NME.
           MOVE SALE-FUND-NBR (SALE-NDX) TO IN-HS-FUND-NBR.
           MOVE SHR-AMT TO IN-HS-SHR-AMT.
           WRITE TEMP-RECORD FROM HIGH-SALE-RECORD.

       0140-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE IS FOR WHEN A MATCHING NUMBER IS NOT FOUND *
      * IN THE TABLE.                                              *
      *                                                            *
      **************************************************************

       0180-NBR-NOT-FOUND.

           MOVE '**** FUND NOT FOUND *****' TO OUT-FUND-NME.
           MOVE '0' TO OUT-SHR-AMT.
           MOVE '0' TO OUT-COMM-AMT.

           COMPUTE TOT-DEP-AMT ROUNDED =
                SALE-DEP-AMT (SALE-NDX) + TOT-DEP-AMT.

       0180-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE IS FOR WHEN A MATCHING NUMBER IS FOUND IN  *
      * THE TABLE.                                                 *
      *                                                            *
      **************************************************************

       0190-NBR-FOUND.

           SET TBL-PRC-NDX TO SALE-SHR-PRC-FLG (SALE-NDX)
           MOVE TBL-FUND-NME (TBL-FUND-NDX) TO OUT-FUND-NME.
           MOVE SALE-DEP-AMT (SALE-NDX) TO DEP-AMT.
           MOVE TBL-FUND-COMM-PCT(TBL-FUND-NDX) TO COMM-PCT.

           COMPUTE TOT-DEP-AMT ROUNDED =
                SALE-DEP-AMT (SALE-NDX) + TOT-DEP-AMT.

           CALL 'CALCSHRS' USING DEP-AMT
                                 TBL-FUND-SHR-PRC
                                       (TBL-FUND-NDX TBL-PRC-NDX)
                                 SHR-AMT.

           PERFORM 0120-COMPUTE-COMMISSION-AMT.

           MOVE SHR-AMT TO OUT-SHR-AMT.

       0190-EXIT. EXIT.
//*
//SYSLIN   DD  DSN=&&OBJMOD1,SPACE=(CYL,(1,1)),
//             DISP=(MOD,PASS)
//*
//SYSPRINT DD SYSOUT=*
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
//SYSMDECK DD  SPACE=(CYL,(1,1))
//*
//******************************************************************
//*                                                                *
//* JSTEP03  THIS ASSEMBLER PROGRAM CALCULATE THE SHARES           *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
//*                                                                *
//* SYSLIB   INPUT:  LOADS IBM LANGUAGE ENVIRONMENT DATA SET       *
//*                                                                *
//* SYSLIN   INPUT:  LOADS THE TEMP &&OBJMOD2                      *
//*                                                                *
//* SYSPRINT OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP03  EXEC PGM=ASMA90,PARM=ASA,COND=(0,LT)
//*
//SYSLIB   DD   DSN=SYS1.MACLIB,DISP=SHR
//*
//SYSIN    DD *
         PRINT  NOGEN                MACRO CALL SUPPRESSION
********************************************************
*                                                      *
*                                                      *
********************************************************
*
CALCSHRS CSECT                       BEGIN CALCSHRS
*
         STM   14,12,12(13)          SAVE CALLER'S REGS
         LR    12,15                 SET R12 TO R15
         USING CALCSHRS,12           ESTABLISH R12 AS 1ST BASE REG
         LA    14,SAVEREGS           R14 -> CURRENT SAVE AREA
         ST    13,4(,14)             SAVE CALLER'S SAVE AREA ADDR
         ST    14,8(,14)             SAVE CURRENT SAVE AREA ADDR
         LR    13,14                 R13 -> CURRENT SAVE AREA
*
         LM    2,4,0(1)              LOAD VARIABLES IN R2 - R4
         ZAP   DEPAMT(11),0(6,2)     LOAD R2(DEPAMT) TO DEPAMT
         ZAP   SHRPRC(3),0(3,3)      LOAD R3(SHRPRC) TO SHRPRC

*
*     CALCULATE THE SHARES AMOUNT SOLD
*
         ZAP   PCALC(11),DEPAMT(11)  COPY DEPAMT INTO PCALC
         SRP   PCALC(11),4,5         SHIFT 4 TIMES
         DP    PCALC(11),SHRPRC(3)   DIVIDE DEPAMT BY SHRPRC
         ZAP   0(8,4),PCALC(8)       COPY ANSWER INTO R4 TO PASS BACK
*
         SR    15,15                 SET RC TO 0
         L     13,4(,13)             R13 -> CALLER'S SAVE AREA
         L     14,12(,13)            RESTORE R14
         LM    0,12,20(13)           RESTORE R0 THROUGH R12
         BR    14                    RETURN TO CALLER
*
         LTORG                       LTORG TO ORGANIZE LITERALS
*
         ORG   CALCSHRS+((*-CALCSHRS+31)/32)*32
         DC    C'HERE IS THE STORAGE FOR CALCSHRS'
*
SAVEREGS DC    18F'0'                MAINREGS FOR STANDARD LINKAGE
PCALC    DC    PL11'0'               CALCULATION HOLDER
DEPAMT   DC    PL11'0'               HOLDS THE PASSED DEPOSIT AMOUNT
SHRPRC   DC    PL3'0'                HOLDS THE PASSED SHARE PRICE
SHRAMT   DC    PL11'0'               HOLDS THE CALCULATED SHARE AMT
         END   CALCSHRS
/*
//*
//SYSLIN   DD DSN=&&OBJMOD2,
//            SPACE=(CYL,(1,1)),
//            DISP=(NEW,PASS,DELETE)
//*
//SYSPRINT DD SYSOUT=*
//*
//SYSUT1   DD SPACE=(CYL,(1,1))
//*
//******************************************************************
//*                                                                *
//* JSTEP04  THIS COBOL PROGRAM CREATE THE HIGH SALES REPORT       *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  INDICATES WHERE DATA SET FROM COBALT          *
//*                  COMPILER IS STORED                            *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
//*                                                                *
//* SYSLIB   INPUT:  LOADS IBM LANGUAGE ENVIRONMENT DATA SET       *
//*                                                                *
//* SYSLIN   INPUT:  LOADS THE TEMP &&OBJMOD3                      *
//*                                                                *
//* SYSPRINT OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP04  EXEC PGM=IGYCRCTL,REGION=0M,COND=(0,LT)
//*
//STEPLIB  DD   DSN=IGY630.SIGYCOMP,DISP=SHR
//*
//SYSLIB   DD   DSN=KC02322.CSCI465.COPYLIB,DISP=SHR
//*
//SYSIN    DD *

       IDENTIFICATION DIVISION.

       PROGRAM-ID.    HISALES.

       ENVIRONMENT DIVISION.

       INPUT-OUTPUT SECTION.

       FILE-CONTROL.

           SELECT FUND-FILE ASSIGN TO FUNDFLE.
           SELECT REPORT-FILE ASSIGN TO RPTFLE.
           SELECT TEMP-FILE ASSIGN TO TEMPFLE.

       DATA DIVISION.

       FILE SECTION.

       FD  FUND-FILE
           RECORDING MODE F.

       01  FUND-RECORD.
           05  IN-FUND-NBR          PIC 9(3).
           05  IN-FUND-NME          PIC X(25).
           05  IN-FUND-COMM-PCT     PIC S9(3)V9(3).

       FD  REPORT-FILE
           RECORDING MODE F
           BLOCK CONTAINS 20 RECORDS.

       01  REPORT-RECORD            PIC X(132).

       FD  TEMP-FILE
           RECORDING MODE F.

       01  TEMP-RECORD.
           05  HS-BROKER-NME        PIC X(25).
           05  HS-FUND-NBR          PIC S9(3)       PACKED-DECIMAL.
           05  HS-SHR-AMT           PIC S9(14)V9(4) PACKED-DECIMAL.

       WORKING-STORAGE SECTION.

       01  FUND-TBL.
           05  TBL-FUND-CTR          PIC S9(3)  BINARY SYNC VALUE 0.
           05  TBL-FUND-NTRY         OCCURS 1 TO 199
                                     DEPENDING ON TBL-FUND-CTR
                                     ASCENDING KEY TBL-FUND-NBR
                                     INDEXED BY TBL-FUND-NDX.
       COPY FUNDTBL.

       01  SUBPROGRAM              PIC X(8) VALUE 'BUILDTBL'.
       01  JOBNAME                 PIC X(8) VALUE 'JOBNAME'.

       01  EOF-FLAG                PIC X     VALUE 'N'.

       01  COUNTERS.
           05  RECORD-CTR           PIC S9(3) BINARY SYNC VALUE 0.
           05  BROKER-CTR           PIC S9(3) PACKED-DECIMAL VALUE 0.
           05  SALES-CTR            PIC S9(3) PACKED-DECIMAL VALUE 0.
           05  LINE-CTR             PIC S9(2) BINARY SYNC VALUE 99.
           05  PAGE-CTR             PIC S9(3) PACKED-DECIMAL VALUE 0.

       01  HIGH-SALE-RECORD.
           05  IN-HS-BROKER-NME     PIC X(25).
           05  IN-HS-FUND-NBR       PIC S9(3) PACKED-DECIMAL.
           05  IN-HS-SHR-AMT        PIC S9(14)V9999
                                       PACKED-DECIMAL VALUE 0.

       01  HEADER-1.
           05  HEADER-DATE.
               10  CURRENT-MONTH    PIC 9(2).
               10                   PIC X VALUE '/'.
               10  CURRENT-DAY      PIC 9(2).
               10                   PIC X VALUE '/'.
               10  CURRENT-YEAR     PIC 9(4).
           05                       PIC X(40) VALUE SPACES.
           05                       PIC X(32)
                              VALUE 'WASHINGTON & LINCOLN INVESTMENTS'.
           05                       PIC X(41) VALUE SPACES.
           05                       PIC X(6) VALUE 'PAGE: '.
           05  OUT-PAGE-CTR         PIC ZZ9.

       01  HEADER-2.
           05  HEADER-TIME.
               10  HOUR             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM             PIC X(2).
           05                       PIC X(45) VALUE SPACES.
           05                       PIC X(24)
                          VALUE 'BROKER HIGH SALES REPORT'.
           05                       PIC X(38) VALUE SPACES.
           05                       PIC X(9) VALUE 'JOBNAME: '.
           05  JOBNME               PIC X(8).

       01  HEADER-3.
           05                       PIC X(18) VALUE SPACES.
           05                       PIC X(25)
                          VALUE 'BROKER NAME              '.
           05                       PIC X(11) VALUE SPACES.
           05                       PIC X(4)  VALUE 'FUND'.
           05                       PIC X(7)  VALUE SPACES.
           05                       PIC X(25)
                          VALUE 'FUND NAME                '.
           05                       PIC X(8)  VALUE SPACES.
           05                       PIC X(18)
                          VALUE '       SHARES SOLD'.
           05                       PIC X(16) VALUE SPACES.

       01  HEADER-4.
           05                       PIC X(18) VALUE SPACES.
           05                       PIC X(25) VALUE ALL '-'.
           05                       PIC X(11) VALUE SPACES.
           05                       PIC X(4)  VALUE ALL '-'.
           05                       PIC X(7)  VALUE SPACES.
           05                       PIC X(25) VALUE ALL '-'.
           05                       PIC X(8)  VALUE SPACES.
           05                       PIC X(18) VALUE ALL '-'.
           05                       PIC X(16) VALUE SPACES.

       01  HS-DETAIL-LINE.
           05                       PIC X(18) VALUE SPACES.
           05  OUT-BROKER-NME       PIC X(25).
           05                       PIC X(11) VALUE SPACES.
           05  OUT-FUND-NBR         PIC ZZZ9.
           05                       PIC X(7)  VALUE SPACES.
           05  OUT-FUND-NME         PIC X(25).
           05                       PIC X(4)  VALUE SPACES.
           05  OUT-SHR-SOLD         PIC Z,ZZZ,ZZZ,ZZZ,ZZ9.9990.
           05                       PIC X(16) VALUE SPACES.

       01  HEADER-TOTALS.
           05                       PIC X(44) VALUE SPACES.
           05                       PIC X(43)
                  VALUE '***** BROKER HIGH SALES REPORT TOTALS *****'.
           05                       PIC X(45) VALUE SPACES.

       01  HEADER-TOTALS-2.
           05                       PIC X(38) VALUE SPACES.
           05                       PIC X(20)
                             VALUE 'NUMBER OF HIGH SALES'.
           05                       PIC X(7) VALUE SPACES.
           05                       PIC X(28)
                             VALUE 'NUMBER OF HIGH SALES BROKERS'.
           05                       PIC X(39) VALUE SPACES.

       01  HEADER-TOTALS-3.
           05                       PIC X(38) VALUE SPACES.
           05                       PIC X(20) VALUE ALL '-'.
           05                       PIC X(7)  VALUE SPACES.
           05                       PIC X(28) VALUE ALL '-'.
           05                       PIC X(39) VALUE SPACES.

       01  HEADER-TOTALS-4.
           05                       PIC X(55) VALUE SPACES.
           05  OUT-RECORD-CTR       PIC ZZ9.
           05                       PIC X(32)  VALUE SPACES.
           05  OUT-BROKER-CTR       PIC ZZ9.
           05                       PIC X(39) VALUE SPACES.

       01  CURRENT-DATE-FIELDS.
           05  CURRENT-DATE.
               10  CURRENT-YEAR     PIC 9(4).
               10  CURRENT-MONTH    PIC 9(2).
               10  CURRENT-DAY      PIC 9(2).
           05  CURRENT-TIME.
               10  CURRENT-HOUR     PIC 9(2).
               10  CURRENT-MINUTE   PIC 9(2).
               10  CURRENT-SECOND   PIC 9(2).
               10  CURRENT-MS       PIC 9(2).
           05  DIFF-FROM-GMT        PIC S9(4).

       PROCEDURE DIVISION.

       0000-MAIN.

           CALL SUBPROGRAM USING FUND-TBL
                                 EOF-FLAG.

           CALL JOBNAME USING JOBNAME.
           MOVE JOBNAME TO JOBNME.

           PERFORM 0100-DATE-TIME.

           OPEN INPUT  TEMP-FILE
                OUTPUT REPORT-FILE.

           READ TEMP-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

           PERFORM 0300-PROCESS-HS-ENTRIES
           VARYING TBL-FUND-NDX FROM 1 BY 1
             UNTIL TBL-FUND-NDX > 198
             OR EOF-FLAG = 'Y'.

           PERFORM 0450-WRITE-TOTALS.

           CLOSE TEMP-FILE
                 REPORT-FILE.

           MOVE 0 TO RETURN-CODE.

           GOBACK.

       0000-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE CALL THE DATE-TIME FUNCTION AND CHANGE IT  *
      * TO 12 HOUR FORMAT CLOCK.                                   *
      *                                                            *
      **************************************************************

       0100-DATE-TIME.

           MOVE FUNCTION CURRENT-DATE TO CURRENT-DATE-FIELDS.
           MOVE CORRESPONDING CURRENT-DATE TO HEADER-DATE.

           MOVE CURRENT-HOUR TO   HOUR.
           MOVE CURRENT-MINUTE TO MINUTE.

           IF HOUR > 12
               MOVE 'PM' TO AMPM
               COMPUTE HOUR = HOUR - 12

           ELSE
               MOVE 'AM' TO AMPM
           END-IF.

       0100-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE PROCESSES THE HIGH SALE FILE               *
      *                                                            *
      **************************************************************
       0200-PROCESS-HS-RECORD.

           MOVE HS-BROKER-NME TO OUT-BROKER-NME.
           MOVE HS-FUND-NBR TO OUT-FUND-NBR.
           MOVE HS-SHR-AMT TO OUT-SHR-SOLD.

           SEARCH ALL TBL-FUND-NTRY
               AT END
                   PERFORM 0350-NOT-FOUND
               WHEN TBL-FUND-NBR(TBL-FUND-NDX) = HS-FUND-NBR
                   PERFORM 0355-FOUND
           END-SEARCH.

           IF LINE-CTR > 17
               PERFORM 0400-WRITE-HS-HEADERS
           END-IF.

           ADD 1 TO LINE-CTR.
           ADD 1 TO SALES-CTR.

           WRITE REPORT-RECORD FROM HS-DETAIL-LINE AFTER 2.

           READ TEMP-FILE INTO HIGH-SALE-RECORD
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0200-EXIT. EXIT.

      **************************************************************
      *                                                            *
      *                                                            *
      **************************************************************

       0300-PROCESS-HS-ENTRIES.

           PERFORM 0200-PROCESS-HS-RECORD.

           ADD 1 TO BROKER-CTR.

           READ TEMP-FILE
               AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0300-EXIT. EXIT.

      **************************************************************
      *                                                            *
      *                                                            *
      **************************************************************

       0350-NOT-FOUND.

       0350-EXIT. EXIT.

      **************************************************************
      *                                                            *
      *                                                            *
      **************************************************************

       0355-FOUND.

           MOVE TBL-FUND-NME (TBL-FUND-NDX) TO OUT-FUND-NME.

       0355-EXIT. EXIT.

      **************************************************************
      *                                                            *
      *                                                            *
      **************************************************************

       0400-WRITE-HS-HEADERS.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-2 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-4 AFTER 1.
           WRITE REPORT-RECORD FROM HS-DETAIL-LINE AFTER 2.

           MOVE 0 TO LINE-CTR.

       0400-EXIT. EXIT.

      **************************************************************
      *                                                            *
      *                                                            *
      **************************************************************

       0450-WRITE-TOTALS.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.
           MOVE SALES-CTR TO OUT-RECORD-CTR.
           MOVE BROKER-CTR TO OUT-BROKER-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-2 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-TOTALS AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-TOTALS-2 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-TOTALS-3 AFTER 1.

           MOVE 0 TO LINE-CTR.

       0450-EXIT. EXIT.

//SYSLIN   DD  DSN=&&OBJMOD3,
//             SPACE=(TRK,(3,3)),
//             DISP=(NEW,PASS,DELETE)
//*
//SYSPRINT DD   SYSOUT=*
//*
//SYSUT1   DD   SPACE=(CYL,(1,1))
//SYSUT2   DD   SPACE=(CYL,(1,1))
//SYSUT3   DD   SPACE=(CYL,(1,1))
//SYSUT4   DD   SPACE=(CYL,(1,1))
//SYSUT5   DD   SPACE=(CYL,(1,1))
//SYSUT6   DD   SPACE=(CYL,(1,1))
//SYSUT7   DD   SPACE=(CYL,(1,1))
//SYSUT8   DD   SPACE=(CYL,(1,1))
//SYSUT9   DD   SPACE=(CYL,(1,1))
//SYSUT10  DD   SPACE=(CYL,(1,1))
//SYSUT11  DD   SPACE=(CYL,(1,1))
//SYSUT12  DD   SPACE=(CYL,(1,1))
//SYSUT13  DD   SPACE=(CYL,(1,1))
//SYSUT14  DD   SPACE=(CYL,(1,1))
//SYSUT15  DD   SPACE=(CYL,(1,1))
//SYSMDECK DD   SPACE=(CYL,(1,1))
//*
//******************************************************************
//*                                                                *
//* JSTEP05 BINDS THE 3 OBJMODS TOGETHER AND CREATES A LOAD MODULE *
//*         CONTAINING THE SALESRPT, CALCSHR, AND HISALES BECAUSE  *
//*         BOTH CALCSHR AND HISALES ARE BEING CALLED STATICALLY   *
//*         FROM SALESRPT.                                         *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
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
//JSTEP05  EXEC PGM=HEWL,COND=(0,LT)
//*
//SYSLIB   DD   DSN=CEE.SCEELKED,DISP=SHR
//*
//SYSLIN   DD   DSN=&&OBJMOD1,DISP=(OLD,DELETE,DELETE)
//         DD   DSN=&&OBJMOD2,DISP=(OLD,DELETE,DELETE)
//         DD   DSN=&&OBJMOD3,DISP=(OLD,DELETE,DELETE)
//         DD   *
   ENTRY SALESRPT
   MODE AMODE(24)
//*
//SYSLMOD  DD   DSN=KC03E6A.CSCI465.LOADLIB(SALESRPT),
//             SPACE=(1024,(50,20,1)),DSNTYPE=LIBRARY,
//             DISP=(MOD,KEEP,KEEP)
//*
//SYSPRINT DD   SYSOUT=*
//*
//******************************************************************
//*                                                                *
//* JSTEP06 OPENS SORTED VERSION OF THE FUNDS FILE, FILL THE       *
//*         TABLE'S FIRST DIMENSION, CLOSE SORTED FILE, OPEN PRICES*
//*         FILE, FILL TABLE'S SECOND DIMENSION AND RETURN TO      *
//*         SALESRPT. THIS SUBPROGRAM WILL BE CALLED DYNAMICALLY.  *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
//*                                                                *
//* SYSLIB   INPUT:  LOADS IBM LANGUAGE ENVIRONMENT DATA SET       *
//*                                                                *
//* SYSLIN   INPUT:  LOADS THE TEMP &&OBJMOD                       *
//*                                                                *
//*                                                                *
//* SYSPRINT OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP06  EXEC PGM=IGYCRCTL,REGION=0M,COND=(0,LT)
//*
//STEPLIB  DD   DSN=IGY630.SIGYCOMP,DISP=SHR
//*
//SYSLIB   DD   DSN=KC02322.CSCI465.COPYLIB,DISP=SHR
//*
//SYSIN    DD   *

       IDENTIFICATION DIVISION.

       PROGRAM-ID.    BUILDTBL.

       ENVIRONMENT DIVISION.

       INPUT-OUTPUT SECTION.

       FILE-CONTROL.

           SELECT FUND-FILE ASSIGN TO FUNDFLE.
           SELECT PRICE-FILE ASSIGN TO PRCFLE.

       DATA DIVISION.

       FILE SECTION.

       FD  FUND-FILE
           RECORDING MODE F.

       01  FUND.
           05  IN-FUND-NBR        PIC 9(3).
           05  IN-FUND-NME        PIC X(25).
           05  IN-FUND-COMM-PCT   PIC S9(3)V9(3).
           05                     PIC X(46).

       FD  PRICE-FILE
           RECORDING MODE F.

       01  PRICE.
           05  IN-FUND-SHR-PRC    OCCURS 3
                                  PIC S9(3)V99.
           05  FILLER             PIC X(65).


       WORKING-STORAGE SECTION.

       01  EOF-FLAG               PIC X  VALUE 'N'.
       01  FUND-SUB               PIC S9 VALUE 0.

       LINKAGE SECTION.

       01  FUND-TBL.
           05  TBL-FUND-CTR          PIC S9(3)  BINARY SYNC VALUE 0.
           05  TBL-FUND-NTRY         OCCURS 1 TO 199
                                     DEPENDING ON TBL-FUND-CTR
                                     ASCENDING KEY TBL-FUND-NBR
                                     INDEXED BY TBL-FUND-NDX.

       COPY FUNDTBL.

       PROCEDURE DIVISION USING FUND-TBL.

       0000-MAIN.

           OPEN INPUT FUND-FILE.

           READ FUND-FILE
           END-READ.

           PERFORM 0100-PROCESS-FUND VARYING TBL-FUND-NDX FROM 1 BY 1
             UNTIL TBL-FUND-NDX > 198
                OR EOF-FLAG = 'Y'.

           CLOSE FUND-FILE.

           OPEN INPUT PRICE-FILE.

           READ PRICE-FILE
           END-READ.

           PERFORM 0200-PROCESS-SALE VARYING TBL-FUND-NDX FROM 1 BY 1
             UNTIL TBL-FUND-NDX > 198
                OR EOF-FLAG = 'Z'.

           CLOSE PRICE-FILE.

           MOVE 0 TO RETURN-CODE.

           GOBACK.

       0000-EXIT. EXIT.

       0100-PROCESS-FUND.

           ADD 1 TO TBL-FUND-CTR.

           MOVE IN-FUND-NBR TO TBL-FUND-NBR (TBL-FUND-NDX).
           MOVE IN-FUND-NME TO TBL-FUND-NME (TBL-FUND-NDX).
           MOVE IN-FUND-COMM-PCT
           TO TBL-FUND-COMM-PCT (TBL-FUND-NDX).

           READ FUND-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0100-EXIT. EXIT.

       0200-PROCESS-SALE.

           PERFORM VARYING FUND-SUB FROM 1 BY 1
             UNTIL FUND-SUB > 3

           MOVE IN-FUND-SHR-PRC (FUND-SUB) TO
              TBL-FUND-SHR-PRC (TBL-FUND-NDX, FUND-SUB)

           END-PERFORM.

           READ PRICE-FILE
             AT END MOVE 'Z' TO EOF-FLAG
           END-READ.

       0200-EXIT. EXIT.
//*
//SYSLIN   DD DSN=&&OBJMOD4,
//            SPACE=(TRK,(3,3)),
//            DISP=(NEW,PASS,DELETE)
//*
//SYSPRINT DD SYSOUT=*
//*
//SYSUT1   DD   SPACE=(CYL,(1,1))
//SYSUT2   DD   SPACE=(CYL,(1,1))
//SYSUT3   DD   SPACE=(CYL,(1,1))
//SYSUT4   DD   SPACE=(CYL,(1,1))
//SYSUT5   DD   SPACE=(CYL,(1,1))
//SYSUT6   DD   SPACE=(CYL,(1,1))
//SYSUT7   DD   SPACE=(CYL,(1,1))
//SYSUT8   DD   SPACE=(CYL,(1,1))
//SYSUT9   DD   SPACE=(CYL,(1,1))
//SYSUT10  DD   SPACE=(CYL,(1,1))
//SYSUT11  DD   SPACE=(CYL,(1,1))
//SYSUT12  DD   SPACE=(CYL,(1,1))
//SYSUT13  DD   SPACE=(CYL,(1,1))
//SYSUT14  DD   SPACE=(CYL,(1,1))
//SYSUT15  DD   SPACE=(CYL,(1,1))
//SYSMDECK DD   SPACE=(CYL,(1,1))
//******************************************************************
//*                                                                *
//* JSTEP07 BINDS THE BUILDTBL PROGRAM AND PRODUCE A PROGRAM OBJECT*
//*         SO THAT IT CAN BE CALLED DYNAMICALLY.                  *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
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
//JSTEP07  EXEC PGM=HEWL,COND=(0,LT)
//*
//SYSLIB   DD DSN=CEE.SCEELKED,DISP=SHR
//*
//SYSLIN   DD DSN=&&OBJMOD4,DISP=(OLD,DELETE,DELETE)
//*
//SYSLMOD  DD DSN=KC03E6A.CSCI465.LOADLIB(BUILDTBL),
//            SPACE=(1024,(50,20,1)),DSNTYPE=LIBRARY,
//            DISP=(MOD,KEEP,KEEP)
//*
//SYSPRINT DD SYSOUT=*
//*
//******************************************************************
//*                                                                *
//* JSTEP08 FETCH THE PROGRAM                                      *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  LOAD FROM STUDENT LIBRARY                     *
//*                                                                *
//* SALESFLE INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE           *
//*                                                                *
//* FUNDFLE  INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE (FUNDS)   *
//*                                                                *
//* TEMPFLE  INPUT:  TEMPORARY DATA SET FOR HIGH SALERS            *
//*                                                                *
//* PRCFLE   INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE (PRICE)   *
//*                                                                *
//* TRANFLE  INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE (SALES)   *
//*                                                                *
//* RPTFLE   OUTPUT: OUTPUT FOR THE COBOL PROGRAM WRITTEN TO       *
//*                  STANDARD OUTPUT                               *
//*                                                                *
//* PRINTOUT OUTPUT: PRINT TO STANDARD OUTPUT                      *
//*                                                                *
//* SYSUDUMP OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP08  EXEC PGM=SALESRPT,COND=(0,LT)
//*
//STEPLIB  DD   DSN=KC03E6A.CSCI465.LOADLIB,DISP=SHR
//         DD   DSN=KC02322.CSCI465.LOADLIB,DISP=SHR
//FUNDFLE  DD   DSN=&&SORTED,DISP=(OLD,DELETE,DELETE)
//TEMPFLE  DD   SPACE=(TRK,(1,1))
//PRCFLE   DD   DSN=KC02322.CSCI465.ASNDATA(PRICES),DISP=SHR
//SALESFLE DD   DSN=KC02322.CSCI465.DATA7(SALES),DISP=SHR
//RPTFLE   DD   SYSOUT=*
//PRINTOUT DD   SYSOUT=*
//SYSUDUMP DD   SYSOUT=*
//
//*