//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H,REGION=0M
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 5        FALL 2022         *
//*                                                               *
//* PROGRAM NAME: COBOL 3  	  © 2022 Long F. Huang                *
//* PROGRAMMER:   LONG FANG HUANG                                 *
//* DUE DATE:     10/21/2022                                      *
//*                                                               *
//* FUNCTION: THIS PROGRAM READS INPUT DATA RECORDS               *
//*            AND THEN WRITES THEM TO STANDARD OUTPUT.           *
//*                                                               *
//* INPUT: SALESFLE - THE INPUT DATA RECORDS READ IN.               *
//*                                                               *
//* OUTPUT: OUTDATA - THE INPUT DATA RECORDS WRITTEN              *
//*                    OUT.                                       *
//*                                                               *
//* NOTES: NONE                                                   *
//*****************************************************************
//*
//******************************************************************
//*                                                                *
//* JSTEP01 COMPILE THE WRITTEN COBALT PROGRAMUSING COBALT COMPILER*
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  INDICATES WHERE DATA SET FROM COBALT          *
//*                  COMPILER IS STORED                            *
//* SYSIN    INPUT:  INDICATES THE WRITTEN COBALT PROGRAM          *
//*                                                                *
//******************************************************************
//JSTEP01  EXEC PGM=IGYCRCTL,PARM=APOST
//STEPLIB  DD   DSN=IGY630.SIGYCOMP,DISP=SHR
//         DD   DSN=CEE.SCEERUN,DISP=SHR
//         DD   DSN=CEE.SCEERUN2,DISP=SHR
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
           SELECT REPORT-FILE ASSIGN TO RPTFLE.
           SELECT TEMP-FILE ASSIGN TO TEMPFLE.

       DATA DIVISION.

       FILE SECTION.

       FD  SALES-FILE
           RECORDING MODE F.

       01  SALE-RECORD.
           05  IN-BRANCH-NME        PIC X(20).
           05  IN-BROKER-NME        PIC X(25).
           05  IN-DEP-AMT           PIC S9(8)V99.
           05  UNUSED               PIC X(4).
           05  IN-COMM-FLG          PIC S9.
           05  UNUSED               PIC X(20).

       FD  REPORT-FILE
           RECORDING MODE F
           BLOCK CONTAINS 20 RECORDS.

       01  REPORT-RECORD            PIC X(132).

       FD  TEMP-FILE
           RECORDING MODE F.

       01  TEMP-RECORD.
           05  HS-BROKER-NME        PIC X(25).
           05  HS-SHR-AMT           PIC S9(14)V9999 PACKED-DECIMAL.

       WORKING-STORAGE SECTION.

       01  FUND-RECORD.
           05  IN-SHR-PRC           PIC S9(3)V99.
           05  IN-FUND-NME          PIC X(35).
           05  IN-COMM-PCT-1        PIC S9(3)V999.
           05  IN-COMM-PCT-2        PIC S9(3)V999.
           05  IN-COMM-PCT-3        PIC S9(3)V999.
           05  UNUSED               PIC X(22).

       01  EOF-FLAG                 PIC X     VALUE 'N'.
       01  EOF-FLAG2                PIC X     VALUE 'N'.

       01  COUNTERS.
           05  RECORD-CTR           PIC S9(3) BINARY SYNC VALUE 0.
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
           05  IN-HS-SHR-AMT        PIC S9(14)V9999
                                       PACKED-DECIMAL VALUE 0.

       01  VARIABLES.
           05  DEP-AMT              PIC S9(12)V99
                                       PACKED-DECIMAL VALUE 0.
           05  SHR-AMT              PIC S9(14)V9999
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
           05                       PIC X(38) VALUE SPACES.
           05  OUT-FUND-NME         PIC X(35).
           05                       PIC X(40) VALUE SPACES.
           05                       PIC X(6) VALUE 'PAGE: '.
           05  OUT-PAGE-CTR         PIC ZZ9.

       01  HEADER-2.
           05  HEADER-TIME.
               10  HOUR             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM             PIC X(2).
           05                       PIC X(40) VALUE SPACES.
           05                       PIC X(35)
                          VALUE 'BROKER SALES AND COMMISSIONS REPORT'.
           05                       PIC X(47) VALUE SPACES.

       01  HEADER-3.
           05  SHARE-PRICE.
               10                   PIC X(55) VALUE SPACES.
               10                   PIC X(13) VALUE 'SHARE PRICE: '.
               10  OUT-SHR-PRC      PIC $$$9.99.
               10                   PIC X(59) VALUE SPACES.

       01  HEADER-4.
           05                       PIC X(20)
                             VALUE 'BRANCH NAME         '.
           05                       PIC X(13) VALUE SPACES.
           05                       PIC X(25)
                             VALUE 'BROKER NAME              '.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(14)
                             VALUE 'DEPOSIT AMOUNT'.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(18)
                             VALUE '      SHARE AMOUNT'.
           05                       PIC X(10) VALUE SPACES.
           05                       PIC X(14)
                             VALUE '    COMMISSION'.

       01  HEADER-5.
           05                       PIC X(20)
                             VALUE '--------------------'.
           05                       PIC X(13) VALUE SPACES.
           05                       PIC X(25)
                             VALUE '-------------------------'.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(14)
                             VALUE '--------------'.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(18)
                             VALUE '------------------'.
           05                       PIC X(10) VALUE SPACES.
           05                       PIC X(14)
                             VALUE '--------------'.

       01  DETAIL-LINE.
           05  OUT-BRANCH-NME       PIC X(20).
           05  FILLER               PIC X(13) VALUE SPACES.
           05  OUT-BROKER-NME       PIC X(25).
           05  FILLER               PIC X(9) VALUE SPACES.
           05  OUT-DEP-AMT          PIC $$$,$$$,$$9.99.
           05  FILLER               PIC X(9) VALUE SPACES.
           05  OUT-SHR-AMT          PIC ZZZ,ZZZ,ZZ9.9990.
           05  FILLER               PIC X(10) VALUE SPACES.
           05  OUT-COMM-AMT         PIC $$$,$$$,$$9.99.

       01  HEADER-TOTALS.
           05  HEADER-TIME.
               10  HOUR2             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE2           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM2             PIC X(2).
           05                       PIC X(37) VALUE SPACES.
           05                       PIC X(42)
                    VALUE 'BROKER SALES AND COMMISSIONS REPORT TOTALS'.
           05                       PIC X(45) VALUE SPACES.

       01  HEADER-TOTALS3.
           05                       PIC X(39) VALUE SPACES.
           05                       PIC X(15) VALUE 'NUMBER OF SALES'.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE 'TOTAL SALES AMOUNT'.
           05                       PIC X(5) VALUE SPACES.
           05                       PIC X(22)
                                       VALUE '    TOTAL SHARE AMOUNT'.
           05                       PIC X(6) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE '  TOTAL COMMISSION'.

       01  HEADER-TOTALS4.
           05                       PIC X(39) VALUE SPACES.
           05                       PIC X(15) VALUE '---------------'.
           05                       PIC X(9) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE '------------------'.
           05                       PIC X(5) VALUE SPACES.
           05                       PIC X(22)
                                       VALUE '----------------------'.
           05                       PIC X(6) VALUE SPACES.
           05                       PIC X(18)
                                       VALUE '------------------'.

       01  HEADER-HS.
           05                       PIC X(37) VALUE SPACES.
           05                       PIC X(25)
                                     VALUE '   HIGH SALES BROKER NAME'.
           05                       PIC X(10) VALUE SPACES.
           05                       PIC X(23)
                                     VALUE 'HIGH SALES SHARE AMOUNT'.
           05                       PIC X(37) VALUE SPACES.

       01  HEADER-HS-2.
           05                       PIC X(37) VALUE SPACES.
           05                       PIC X(25)
                                     VALUE '-------------------------'.
           05                       PIC X(10) VALUE SPACES.
           05                       PIC X(23)
                                     VALUE '-----------------------'.
           05                       PIC X(37) VALUE SPACES.

       01  HIGH-SALES-LINE.
           05                       PIC X(37) VALUE SPACES.
           05  OUT-HS-BROKER-NME    PIC X(25).
           05                       PIC X(10) VALUE SPACES.
           05  OUT-HS-SHR-AMT       PIC Z,ZZZ,ZZZ,ZZZ,ZZ9.9990.
           05                       PIC X(37) VALUE SPACES.

       01  HEADER-HS-3.
           05  HEADER-HS-TIME.
               10  HOUR3             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE3           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM3             PIC X(2).
           05                       PIC X(44) VALUE SPACES.
           05                       PIC X(25)
                    VALUE 'BROKER LARGE SALES REPORT'.
           05                       PIC X(55) VALUE SPACES.

       01  HEADER-HS-TOTALS.
           05  HEADER-HS-TIME-2.
               10  HOUR4             PIC 9(2).
               10                   PIC X VALUE ':'.
               10  MINUTE4           PIC 9(2).
               10                   PIC X VALUE ' '.
               10  AMPM4             PIC X(2).
           05                       PIC X(41) VALUE SPACES.
           05                       PIC X(32)
                    VALUE 'BROKER LARGE SALES REPORT TOTALS'.
           05                       PIC X(51) VALUE SPACES.

       01  TOTALS-HS.
           05                       PIC X(34) VALUE SPACES.
           05                       PIC X(28)
                                VALUE 'NUMBER OF HIGH SALES BROKERS'.
           05                       PIC X(4) VALUE SPACES.
           05                       PIC X(29)
                                VALUE 'TOTAL HIGH SALES SHARE AMOUNT'.
           05                       PIC X(37) VALUE SPACES.

       01  TOTALS-HS-1.
           05                       PIC X(34) VALUE SPACES.
           05                       PIC X(28)
                                VALUE '----------------------------'.
           05                       PIC X(4) VALUE SPACES.
           05                       PIC X(29)
                                VALUE '-----------------------------'.
           05                       PIC X(37) VALUE SPACES.

       01  TOTALS-HS-2.
           05                       PIC X(59) VALUE SPACES.
           05  OUT-HS-SALE-CTR      PIC ZZ9.
           05                       PIC X(11) VALUE SPACES.
           05  OUT-HS-TOT-SHR-AMT   PIC Z,ZZZ,ZZZ,ZZZ,ZZ9.9990.
           05                       PIC X(37) VALUE SPACES.

       01  TOTALS-LINE.
           05                       PIC X(51) VALUE SPACES.
           05  OUT-SALE-REC         PIC ZZ9.
           05                       PIC X(9) VALUE SPACES.
           05  OUT-TOT-DEP-AMT      PIC $$$,$$$,$$$,$$9.99.
           05                       PIC X(5) VALUE SPACES.
           05  OUT-TOT-SHR-AMT      PIC Z,ZZZ,ZZZ,ZZZ,ZZ9.9990.
           05                       PIC X(6) VALUE SPACES.
           05  OUT-TOT-COMM-AMT     PIC $$$,$$$,$$$,$$9.99.

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

           PERFORM 0100-DATE-TIME.

           OPEN INPUT  SALES-FILE
                OUTPUT TEMP-FILE
                OUTPUT REPORT-FILE.

           READ SALES-FILE INTO FUND-RECORD.

           READ SALES-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

           PERFORM 0100-PROCESS-RECORD
             UNTIL EOF-FLAG = 'Y'.

           PERFORM 0130-WRITE-TOTALS.

           CLOSE TEMP-FILE
                 SALES-FILE.

           OPEN INPUT TEMP-FILE.

           READ TEMP-FILE INTO HIGH-SALE-RECORD
               AT END MOVE 'Y' TO EOF-FLAG2
           END-READ.

           MOVE 0 TO PAGE-CTR.
           MOVE 99 TO LINE-CTR.

           PERFORM 0160-PROCESS-HS-RECORD
               UNTIL EOF-FLAG2 = 'Y'.

           PERFORM 0170-WRITE-HS-TOTALS.

           CLOSE TEMP-FILE
                 REPORT-FILE.

           MOVE 0 TO RETURN-CODE.

           STOP RUN.

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
                                  HOUR2
                                  HOUR3
                                  HOUR4.

           MOVE CURRENT-MINUTE TO MINUTE
                                  MINUTE2
                                  MINUTE3
                                  MINUTE4.

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

           IF HOUR3 > 12
               MOVE 'PM' TO AMPM3
               COMPUTE HOUR3 = HOUR3 - 12

           ELSE
               MOVE 'AM' TO AMPM3
           END-IF.

           IF HOUR4 > 12
               MOVE 'PM' TO AMPM4
               COMPUTE HOUR4 = HOUR4 - 12

           ELSE
               MOVE 'AM' TO AMPM4
           END-IF.

      **************************************************************
      * THIS SUBROUTINE PROCESSES THE ENTIRE RECORD, COMPUTE TOTAL *
      * AMOUNT OF DEPOSIT.                                         *
      *                                                            *
      **************************************************************

       0100-PROCESS-RECORD.

           MOVE IN-BRANCH-NME TO OUT-BRANCH-NME.
           MOVE IN-BROKER-NME TO OUT-BROKER-NME.
           MOVE IN-DEP-AMT TO OUT-DEP-AMT.

           PERFORM 0120-COMPUTE-SHR-AMNT-AND-COMM.

           COMPUTE TOT-DEP-AMT ROUNDED = IN-DEP-AMT + TOT-DEP-AMT.

           IF LINE-CTR > 17
               PERFORM 0110-WRITE-HEADERS
           END-IF.

           WRITE REPORT-RECORD FROM DETAIL-LINE AFTER 2.

           ADD 1 TO LINE-CTR.
           ADD 1 TO RECORD-CTR.

           READ SALES-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0100-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE TALLIES PAGE NUMBER AND PRINT THE HEADER   *
      *                                                            *
      **************************************************************

       0110-WRITE-HEADERS.

           MOVE IN-FUND-NME TO OUT-FUND-NME.
           MOVE IN-SHR-PRC  TO OUT-SHR-PRC.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-2 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-4 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-5 AFTER 1.

           MOVE 0 TO LINE-CTR.

       0110-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE CALCULATES COMMISSION AND THE SHARE AMOUNT *
      * AND PROCESS HIGH SALE BROKERS (>50,000 SHARES) TO TEMP     *
      * DATA SET BY CALLING 01400-ADD-TO-TEMP-FILE SUBROUTINE.     *
      *                                                            *
      **************************************************************

       0120-COMPUTE-SHR-AMNT-AND-COMM.

           COMPUTE OUT-SHR-AMT ROUNDED = IN-DEP-AMT / IN-SHR-PRC.

           MOVE OUT-SHR-AMT TO SHR-AMT.

           IF SHR-AMT > 50000
               PERFORM 0140-ADD-TO-TEMP-FILE
           END-IF.

           IF IN-COMM-FLG = 1
               COMPUTE OUT-COMM-AMT ROUNDED =
                   IN-DEP-AMT * IN-COMM-PCT-1 / 100

               COMPUTE TOT-COMM-AMT ROUNDED =
                   (IN-DEP-AMT * IN-COMM-PCT-1 / 100) + TOT-COMM-AMT
           END-IF.

           IF IN-COMM-FLG = 2
               COMPUTE OUT-COMM-AMT ROUNDED =
                   IN-DEP-AMT * IN-COMM-PCT-2 / 100

               COMPUTE TOT-COMM-AMT ROUNDED =
                   (IN-DEP-AMT * IN-COMM-PCT-2 / 100) + TOT-COMM-AMT
           END-IF.

           IF IN-COMM-FLG = 3
               COMPUTE OUT-COMM-AMT ROUNDED =
                   IN-DEP-AMT * IN-COMM-PCT-3 / 100

               COMPUTE TOT-COMM-AMT ROUNDED =
                   (IN-DEP-AMT * IN-COMM-PCT-3 / 100) + TOT-COMM-AMT
           END-IF.

           COMPUTE TOT-SHR-AMT ROUNDED =
                   (IN-DEP-AMT / IN-SHR-PRC) + TOT-SHR-AMT.

       0120-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE PRINTS THE TOTALED AMOUNT OF RELEVANT DATA *
      *                                                            *
      **************************************************************

       0130-WRITE-TOTALS.

           MOVE IN-FUND-NME TO OUT-FUND-NME.
           MOVE IN-SHR-PRC  TO OUT-SHR-PRC.
           MOVE TOT-COMM-AMT TO OUT-TOT-COMM-AMT.
           MOVE TOT-DEP-AMT TO OUT-TOT-DEP-AMT.
           MOVE RECORD-CTR TO OUT-SALE-REC.
           MOVE TOT-SHR-AMT TO OUT-TOT-SHR-AMT.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-TOTALS AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-TOTALS3 AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-TOTALS4 AFTER 1.
           WRITE REPORT-RECORD FROM TOTALS-LINE AFTER 2.

           MOVE 0 TO LINE-CTR.

       0130-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE MOVE THE SELECTED DATA INTO A TEMPORARY    *
      * DATA SET.                                                  *
      *                                                            *
      **************************************************************

       0140-ADD-TO-TEMP-FILE.

           MOVE IN-BROKER-NME TO IN-HS-BROKER-NME.
           MOVE SHR-AMT TO IN-HS-SHR-AMT.
           WRITE TEMP-RECORD FROM HIGH-SALE-RECORD.

       0140-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE WRITES THE HEADER FOR THE TEMP DATA SET    *
      * TO DISPLAY HIGH SALE BROKERS (>50,000)                     *
      *                                                            *
      **************************************************************

       0150-WRITE-HS-HEADERS.

           ADD 1 TO PAGE-CTR.

           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-HS-3 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-HS AFTER 2.
           WRITE REPORT-RECORD FROM HEADER-HS-2 AFTER 1.

           MOVE 0 TO LINE-CTR.

       0150-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE PROCESSES THE TEMPORARY RECORD, COMPUTE    *
      * TOTAL SHARE OF ALL BROKERS IN THIS RECORD.                 *
      *                                                            *
      **************************************************************

       0160-PROCESS-HS-RECORD.

           MOVE HS-BROKER-NME TO OUT-HS-BROKER-NME.
           MOVE HS-SHR-AMT TO OUT-HS-SHR-AMT.

           COMPUTE TOT-HS-SHR-AMT =
                   TOT-HS-SHR-AMT + HS-SHR-AMT.

           IF LINE-CTR > 17
               PERFORM 0150-WRITE-HS-HEADERS
           END-IF.

           ADD 1 TO LINE-CTR.
           ADD 1 TO HS-CTR.

           WRITE REPORT-RECORD FROM HIGH-SALES-LINE AFTER 2.

           READ TEMP-FILE INTO HIGH-SALE-RECORD
             AT END MOVE 'Y' TO EOF-FLAG2
           END-READ.

       0160-EXIT. EXIT.

      **************************************************************
      * THIS SUBROUTINE WRITES TOTAL FOR THE TEMPORARY RECORD DATA *
      *                                                            *
      **************************************************************

       0170-WRITE-HS-TOTALS.

           ADD 1 TO PAGE-CTR.
           MOVE PAGE-CTR TO OUT-PAGE-CTR.

           MOVE HS-CTR TO OUT-HS-SALE-CTR.
           MOVE TOT-HS-SHR-AMT TO OUT-HS-TOT-SHR-AMT.

           WRITE REPORT-RECORD FROM HEADER-1 AFTER PAGE.
           WRITE REPORT-RECORD FROM HEADER-HS-TOTALS AFTER 1.
           WRITE REPORT-RECORD FROM HEADER-3 AFTER 2.
           WRITE REPORT-RECORD FROM TOTALS-HS AFTER 2.
           WRITE REPORT-RECORD FROM TOTALS-HS-1 AFTER 1.
           WRITE REPORT-RECORD FROM TOTALS-HS-2 AFTER 2.

           MOVE 0 TO LINE-CTR.

       0170-EXIT. EXIT.
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
//SYSMDECK DD  SPACE=(CYL,(1,1))
//*
//******************************************************************
//*                                                                *
//* JSTEP02 BINDS THE PROGRAM AND PRODUCE A PROGRAM OBJECT         *
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
//JSTEP02  EXEC PGM=HEWL,COND=(0,LT)
//SYSLIB   DD   DSN=CEE.SCEELKED,DISP=SHR
//SYSLIN   DD   DSN=&&OBJMOD,DISP=(OLD,DELETE)
//*
//SYSLMOD  DD   DSN=KC03E6A.CSCI465.LOADLIB(SALESRPT),
//             SPACE=(1024,(50,20,1)),DSNTYPE=LIBRARY,
//             DISP=(MOD,KEEP,KEEP)
//*
//SYSPRINT DD   SYSOUT=*
//*
//******************************************************************
//*                                                                *
//* JSTEP03 FETCH THE PROGRAM                                      *
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  LOAD FROM STUDENT LIBRARY                     *
//*                                                                *
//* SALESFLE   INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE         *
//*                                                                *
//* RPTFLE  OUTPUT: OUTPUT FOR THE COBOL PROGRAM WRITTEN TO        *
//*                  STANDARD OUTPUT                               *
//*                                                                *
//* PRINTOUT OUTPUT: PRINT TO STANDARD OUTPUT                      *
//*                                                                *
//* SYSUDUMP OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP03  EXEC PGM=SALESRPT,COND=(0,LT)
//STEPLIB  DD   DSN=KC03E6A.CSCI465.LOADLIB,DISP=SHR
//SALESFLE DD   DSN=KC02322.CSCI465.ASNDATA(ASN5DATA),DISP=SHR
//TEMPFLE  DD   SPACE=(TRK,(1,1))
//RPTFLE   DD   SYSOUT=*
//PRINTOUT DD   SYSOUT=*
//SYSUDUMP DD   SYSOUT=*
//
//*
