//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H,REGION=0M
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 4        FALL 2022         *
//*                                                               *
//* PROGRAM NAME: COBOL 3  	  © 2022 Long F. Huang                *
//* PROGRAMMER:   LONG FANG HUANG                                 *
//* DUE DATE:     10/07/2022                                      *
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

       DATA DIVISION.

       FILE SECTION.

       FD  SALES-FILE
           RECORDING MODE F.

       01  SALE-RECORD.
           05  IN-BRANCH-NME        PIC X(20).
           05  IN-BROKER-NME        PIC X(25).
           05  IN-DEP-AMT           PIC S9(8)V99 DISPLAY.
           05  UNUSED               PIC X(25).

       FD  REPORT-FILE
           RECORDING MODE F
           BLOCK CONTAINS 20 RECORDS.

       01  REPORT-RECORD            PIC X(132).

       WORKING-STORAGE SECTION.

       01  EOF-FLAG                 PIC X     VALUE 'N'.

       01  DETAIL-LINE.
           05  OUT-BRANCH-NME       PIC X(20).
           05  FILLER               PIC X(10) VALUE SPACES.
           05  OUT-BROKER-NME       PIC X(25).
           05  FILLER               PIC X(10) VALUE SPACES.
           05  OUT-DEP-AMT          PIC $$$,$$$,$$9.99.

       PROCEDURE DIVISION.

       0000-MAIN.

           OPEN INPUT  SALES-FILE
                OUTPUT REPORT-FILE.

           READ SALES-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

           PERFORM 0100-PROCESS-RECORD
             UNTIL EOF-FLAG = 'Y'.

           CLOSE SALES-FILE
                 REPORT-FILE.

           MOVE 0 TO RETURN-CODE.

           STOP RUN.

       0000-EXIT. EXIT.

       0100-PROCESS-RECORD.

           MOVE IN-BRANCH-NME TO OUT-BRANCH-NME.
           MOVE IN-BROKER-NME TO OUT-BROKER-NME.
           MOVE IN-DEP-AMT TO OUT-DEP-AMT.

           WRITE REPORT-RECORD FROM DETAIL-LINE AFTER 2.

           READ SALES-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0100-EXIT. EXIT.
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
//* SALESFLE   INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE           *
//*                                                                *
//* RPTFLE  OUTPUT: OUTPUT FOR THE COBOL PROGRAM WRITTEN TO       *
//*                  STANDARD OUTPUT                               *
//*                                                                *
//* PRINTOUT OUTPUT: PRINT TO STANDARD OUTPUT                      *
//*                                                                *
//* SYSUDUMP OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP03  EXEC PGM=SALESRPT,COND=(0,LT)
//STEPLIB  DD   DSN=KC03E6A.CSCI465.LOADLIB,DISP=SHR
//SALESFLE DD   DSN=KC02322.CSCI465.ASNDATA(ASN4DATA),DISP=SHR
//RPTFLE   DD   SYSOUT=*
//PRINTOUT DD   SYSOUT=*
//SYSUDUMP DD   SYSOUT=*
//
//*
