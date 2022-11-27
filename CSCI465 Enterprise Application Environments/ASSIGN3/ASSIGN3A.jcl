//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H,REGION=0M
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 3        FALL 2022         *
//*                                                               *
//* PROGRAM NAME: COBOL 3  	  © 2022 Long F. Huang                *
//* PROGRAMMER:   LONG FANG HUANG                                 *
//* DUE DATE:     09/23/2022                                      *
//*                                                               *
//* FUNCTION: THIS PROGRAM READS INPUT DATA RECORDS               *
//*            AND THEN WRITES THEM TO STANDARD OUTPUT.           *
//*                                                               *
//* INPUT: INDATA - THE INPUT DATA RECORDS READ IN.               *
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

       PROGRAM-ID.    COBOL3.
       AUTHOR.        GEOFFREY D DECKER.
       DATE-WRITTEN.  09/10/2022.
       DATE-COMPILED.

       ENVIRONMENT DIVISION.

       INPUT-OUTPUT SECTION.

       FILE-CONTROL.

           SELECT INPUT-FILE ASSIGN TO INDATA.
           SELECT REPORT-FILE ASSIGN TO RPTDATA.

       DATA DIVISION.

       FILE SECTION.

       FD  INPUT-FILE
           RECORDING MODE F.

       01  INPUT-RECORD             PIC X(80).

       FD  REPORT-FILE
           RECORDING MODE F
           BLOCK CONTAINS 20 RECORDS.

       01  REPORT-RECORD            PIC X(132).

       WORKING-STORAGE SECTION.

       01  EOF-FLAG                  PIC X     VALUE 'N'.

       01  RECORD-CTR               PIC S9(3)  BINARY SYNC VALUE 0.

       01  DETAIL-LINE.
           05  OUTPUT-RECORD        PIC X(80).
           05  FILLER               PIC X(52)  VALUE SPACES.

       01  TOTALS-LINE.
           05  FILLER               PIC X(14)  VALUE 'RECORD COUNT: '.
           05  OUT-RECORD-CTR       PIC ZZ9.
           05  FILLER               PIC X(115) VALUE SPACES.

       PROCEDURE DIVISION.

       0000-MAIN.

           OPEN INPUT  INPUT-FILE
                OUTPUT REPORT-FILE.

           READ INPUT-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

           PERFORM 0100-PROCESS-RECORD
             UNTIL EOF-FLAG = 'Y'.

           PERFORM 0200-PROCESS-TOTALS.

           CLOSE INPUT-FILE
                 REPORT-FILE.

           MOVE 0 TO RETURN-CODE.

           STOP RUN.

       0000-EXIT. EXIT.

       0100-PROCESS-RECORD.

           ADD 1 TO RECORD-CTR.

           MOVE INPUT-RECORD TO OUTPUT-RECORD.

           WRITE REPORT-RECORD FROM DETAIL-LINE AFTER 2.

           READ INPUT-FILE
             AT END MOVE 'Y' TO EOF-FLAG
           END-READ.

       0100-EXIT. EXIT.

       0200-PROCESS-TOTALS.

           MOVE RECORD-CTR TO OUT-RECORD-CTR.

           WRITE REPORT-RECORD FROM TOTALS-LINE AFTER 2.

       0200-EXIT. EXIT.
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
//SYSLMOD  DD   DSN=KC03E6A.CSCI465.LOADLIB(COBOL3),
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
//* INDATA   INPUT:  LOAD DATA FROM THE GIVEN INPUT FILE           *
//*                                                                *
//* RPTDATA  OUTPUT: OUTPUT FOR THE COBOL PROGRAM WRITTEN TO       *
//*                  STANDARD OUTPUT                               *
//*                                                                *
//* PRINTOUT OUTPUT: PRINT TO STANDARD OUTPUT                      *
//*                                                                *
//* SYSUDUMP OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//JSTEP03  EXEC PGM=COBOL3,COND=(0,LT)
//STEPLIB  DD   DSN=KC03E6A.CSCI465.LOADLIB,DISP=SHR
//INDATA   DD   DSN=KC02322.CSCI465.ASNDATA(ASN3DATA),DISP=SHR
//RPTDATA  DD   SYSOUT=*
//PRINTOUT DD   SYSOUT=*
//SYSUDUMP DD   SYSOUT=*
//
//*
