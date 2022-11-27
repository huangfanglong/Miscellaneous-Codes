//KC03E6A JOB ,'L.HUANG',MSGCLASS=H
//*
//*****************************************************************
//*                                                               *
//*  CSCI 465               ASSIGNMENT 1        FALL 2022         *
//*                                                               *
//*  DEVELOPER NAME: LONG FANG HUANG                              *
//*        DUE DATE: 08/25/2022                                   *
//*                                                               *
//*  PURPOSE: The purpose of this job is to allocated a new PDSE, *
//*  or partitioned data set extended, that holds load modules.   *
//*  There are two job steps, both running IEFBR14. The           *
//*  first will delete any possible previous version of the       *
//*  PDSE named KC03nnn.CSCI465.LOADLIB. The second creates       *
//*  a new PDSE of the same name. IEFBR14 is one of the           *
//*  most used of all the IBM utilities available.                *
//*  IEFBR14's source module consists only of a CSECT with only   *
//*  standard entry and exit linkage. It accomplishes             *
//*  really nothing as a stand-alone program BUT, as we           *
//*  will soon find out, it has MANY uses for allocating          *
//*  (creating), cataloging, deleting, and un-cataloging          *
//*  data sets. In this two-step job, you are simply              *
//*  executing IEFBR14 twice. The first step deletes any          *
//*  previously-created PDSE that might exist from a prior        *
//*  successful run of the job and the second allocates, or       *
//*  creates, a new one. This PDSE is the second of the           *
//*  three PDSEs that we will need this semester.                 *
//*                                                               *
//*****************************************************************
//*
//JSTEP01  EXEC PGM=IEFBR14
//*
//*  The following DD card deletes an existing PDSE if it already
//*  exists. If it does not exist, the data set is first allocated
//*  and then immediately deleted.
//*
//DD1      DD DSN=KC03E6A.CSCI465.LOADLIB,
//            SPACE=(TRK,(1,1,1)),
//            DISP=(MOD,DELETE,DELETE)
//*
//JSTEP02  EXEC PGM=IEFBR14,COND=(0,LT)
//*
//*  The following DD card allocates a PDSE to hold your
//*  program load module files.
//*
//DD1      DD DSN=KC03E6A.CSCI465.LOADLIB,
//            DCB=(RECFM=U,LRECL=0,BLKSIZE=4096),
//            DSNTYPE=LIBRARY,
//            SPACE=(CYL,(9,5,6)),
//            DISP=(NEW,KEEP,DELETE)
//
