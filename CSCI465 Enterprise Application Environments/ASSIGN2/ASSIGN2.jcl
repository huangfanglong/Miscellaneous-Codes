//KC03E6AA JOB ,'L.HUANG',MSGCLASS=H
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 2        FALL 2022         *
//*                                                               *
//*  DEVELOPER NAME: LONG FANG HUANG                              *
//*        DUE DATE: 09/09/2022                                   *
//*                                                               *
//*  PURPOSE: FETCH A PROGRAM                                     *
//*                                                               *
//*****************************************************************
//*
//JSTEP01  EXEC PGM=READRECS,PARM=ASA
//*
//******************************************************************
//*                                                                *
//* JSTEP01 READS FROM LIBRARY DATA AND PASSES TEMP DATA TO JSTEP02*
//*                                                                *
//* DDNAME           FILE DESCRIPTION                              *
//*                                                                *
//* STEPLIB  INPUT:  LOAD LIBRARY FROM DECKER                      *
//* RECSIN   INPUT:  READ FROM DATA2                               *
//*                                                                *
//* RECSOUT  OUTPUT: CREATES TEMP DATA SET TO BE PASSED            *
//* SYSDUMP  OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//*
//STEPLIB  DD DSN=KC02322.CSCI465.LOADLIB,DISP=SHR
//RECSIN   DD DSN=KC02322.CSCI465.ASNDATA(ASN2DATA),DISP=SHR
//*
//RECSOUT  DD DSN=&&TEMPD,
//            SPACE=(TRK,(1,1)),
//            DISP=(NEW,PASS,DELETE)
//SYSDUMP  DD SYSOUT=*
//*
//****************************************
//*
//JSTEP02  EXEC PGM=WRTERECS,COND=(0,LT)
//*
//******************************************************************
//*                                                                *
//* JSTEP02 RECEIVES TEMP DATA AND WRITES TO OUTPUT.               *
//*                                                                *
//* STEPLIB  INPUT:  LOAD LIBRARY FROM DECKER                      *
//* RECSIN   INPUT:  RECEIVES TEMP DATA FROM JSTEP01               *
//*                                                                *
//* RECSOUT  OUTPUT: PRINTS THE OUTPUT FROM DATA                   *
//* SYSDUMP  OUTPUT: DIAGNOSTIC                                    *
//*                                                                *
//******************************************************************
//*
//STEPLIB  DD DSN=KC02322.CSCI465.LOADLIB,
//            DISP=SHR
//RECSIN   DD DSN=&&TEMPD,DISP=(OLD,DELETE,DELETE)
//*
//RECSOUT  DD SYSOUT=*
//SYSDUMP  DD SYSOUT=*
