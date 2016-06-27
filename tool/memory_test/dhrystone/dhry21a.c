/*
 *************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *
 *  Version:    C, Version 2.1
 *
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 *************************************************************************
 */
  /* 
  forward declaration necessary since Enumeration may not simply be int
  */

#ifndef ROPT
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
#define REG register
#endif

#include <string.h>
#include <stdlib.h>
#include "dhry.h"
#include <target.h>

typedef long TimeFormat;

/* Global Variables: */

#ifdef DISABLEPRINT
#define printf(x)
#else
#define printf(x)	printf x
#endif /* DISABLEPRINT */

#define LXR_EXIT_SUCCESS 0
#define LXR_EXIT_FAILURE 1


#ifdef DISABLE_MALLOC
  char Next_Ptr_Glob_Array[sizeof (Rec_Type)];
  char Ptr_Glob_Array[sizeof (Rec_Type)];
#endif

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

char Reg_Define[] = "Register option selected.";

Enumeration     Func_1 ();

/* variables for time measurement: */

#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */

TimeFormat          Begin_Time,
                End_Time,
                User_Time;

TimeFormat          Microseconds,
                Dhrystones_Per_Second,
                Vax_Mips;

/* end of variables for time measurement */

long Vax, cycle_per_run;
int 
main (void)
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{
  int errors = 0;

  TimeFormat   dtime();

        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs;

        FILE            *Ap;

  unsigned long long    total = 0;

  /* Initializations */

#ifdef ENABLEFILEIO
  if ((Ap = fopen("dhry.res","a+")) == NULL)
    {
       printf(("Can not open dhry.res\n\n"));
       exit(1);
    }
#endif

#ifdef DISABLE_MALLOC
  Next_Ptr_Glob = (Rec_Pointer) Next_Ptr_Glob_Array;
  Ptr_Glob = (Rec_Pointer) Ptr_Glob_Array;
#else
  Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
#endif

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp, 
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

  printf(("\n"));
  printf(("Dhrystone Benchmark, Version 2.1 (Language: C)\n"));
  printf(("\n"));
#if 0  
  if (Reg)
  {
    printf(("Program compiled with 'register' attribute\n"));
    printf(("\n"));
  }
  else
  {
    printf(("Program compiled without 'register' attribute\n"));
    printf(("\n"));
  }
#endif

  printf(("Please give the number of runs through the benchmark: \n"));

#ifndef NUMBER_OF_RUNS
  {
    int n;
    scanf ("%d", &n);
    Number_Of_Runs = n;
  }
#else
  Number_Of_Runs = NUMBER_OF_RUNS;
#endif /* NUMBER_OF_RUNS */

  printf(("\n"));

  printf(("Execution starts, %d runs through Dhrystone\n",Number_Of_Runs));


  /***************/
  /* Start timer */
  /***************/
  Begin_Time = dtime();

  start_hook();
  timer_start();

  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {

    Proc_5();
    Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob);
    for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C'))
          /* then, not executed */
        {
        Proc_6 (Ident_1, &Enum_Loc);
        strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Int_Glob = Run_Index;
        }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
      Int_2_Loc = Int_2_Loc * Int_1_Loc;
      Int_1_Loc = Int_2_Loc / Int_3_Loc;
      Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
      Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */
  } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/
  timer_stop();
  End_Time = dtime();
  printf(("Execution ends\n"));
  printf(("\n"));
  printf(("Final values of the variables used in the benchmark: "));
  printf(("\n"));
  if (Int_Glob != 5) ++errors;
  printf(("Int_Glob:            %d\n", Int_Glob));
  printf(("        should be:   %d\n", 5));
  if (Bool_Glob != 1) ++errors;
  printf(("Bool_Glob:           %d\n", Bool_Glob));
  printf(("        should be:   %d\n", 1));
  if (Ch_1_Glob != 'A') ++errors;
  printf(("Ch_1_Glob:           %c\n", Ch_1_Glob));
  printf(("        should be:   %c\n", 'A'));
  if (Ch_2_Glob != 'B') ++errors;
  printf(("Ch_2_Glob:           %c\n", Ch_2_Glob));
  printf(("        should be:   %c\n", 'B'));
  if (Arr_1_Glob[8] != 7) ++errors;
  printf(("Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]));
  printf(("        should be:   %d\n", 7));
  if (Arr_2_Glob[8][7] != (Number_Of_Runs + 10)) ++errors;
  printf(("Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]));
  printf(("        should be:   Number_Of_Runs + 10\n"));
  printf(("Ptr_Glob->\n"));
  printf(("  Ptr_Comp:          %d\n", (int) Ptr_Glob->Ptr_Comp));
  printf(("        should be:   (implementation-dependent)\n"));
  if (Ptr_Glob->Discr != 0) ++errors;
  printf(("  Discr:             %d\n", Ptr_Glob->Discr));
  printf(("        should be:   %d\n", 0));
  if (Ptr_Glob->variant.var_1.Enum_Comp != 2) ++errors;
  printf(("  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp));
  printf(("        should be:   %d\n", 2));
  if (Ptr_Glob->variant.var_1.Int_Comp != 17) ++errors;
  printf(("  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp));
  printf(("        should be:   %d\n", 17));
  if (strcmp(Ptr_Glob->variant.var_1.Str_Comp,
       "DHRYSTONE PROGRAM, SOME STRING") != 0) ++errors;
  printf(("  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp));
  printf(("        should be:   DHRYSTONE PROGRAM, SOME STRING\n"));
  printf(("Next_Ptr_Glob->\n"));
  printf(("  Ptr_Comp:          %d\n", (int) Next_Ptr_Glob->Ptr_Comp));
  printf(("        should be:   (implementation-dependent), same as above\n"));
  if (Next_Ptr_Glob->Discr != 0) ++errors;
  printf(("  Discr:             %d\n", Next_Ptr_Glob->Discr));
  printf(("        should be:   %d\n", 0));
  if (Next_Ptr_Glob->variant.var_1.Enum_Comp != 1) ++errors;
  printf(("  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp));
  printf(("        should be:   %d\n", 1));
  if (Next_Ptr_Glob->variant.var_1.Int_Comp != 18) ++errors;
  printf(("  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp));
  printf(("        should be:   %d\n", 18));
  if (strcmp(Next_Ptr_Glob->variant.var_1.Str_Comp,
       "DHRYSTONE PROGRAM, SOME STRING") != 0) ++errors;
  printf(("  Str_Comp:          %s\n", Next_Ptr_Glob->variant.var_1.Str_Comp));
  printf(("        should be:   DHRYSTONE PROGRAM, SOME STRING\n"));
  if (Int_1_Loc != 5) ++errors;
  printf(("Int_1_Loc:           %d\n", Int_1_Loc));
  printf(("        should be:   %d\n", 5));
  if (Int_2_Loc != 13) ++errors;
  printf(("Int_2_Loc:           %d\n", Int_2_Loc));
  printf(("        should be:   %d\n", 13));
  if (Int_3_Loc != 7) ++errors;
  printf(("Int_3_Loc:           %d\n", Int_3_Loc));
  printf(("        should be:   %d\n", 7));
  if (Enum_Loc != 1) ++errors;
  printf(("Enum_Loc:            %d\n", Enum_Loc));
  printf(("        should be:   %d\n", 1));
  if (strcmp(Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING") != 0) ++errors;
  printf(("Str_1_Loc:           %s\n", Str_1_Loc));
  printf(("        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n"));
  if (strcmp(Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING") != 0) ++errors;
  printf(("Str_2_Loc:           %s\n", Str_2_Loc));
  printf(("        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n"));
  printf(("\n"));

  printf(("-------------------CPU Statistic --------------------\n"));
  Vax_caculate();

  msg_hook(Number_Of_Runs);
  User_Time = End_Time - Begin_Time;
  if (User_Time < Too_Small_Time)
  {
    printf(("Measured time too small to obtain meaningful results\n"));
    printf(("Please increase number of runs\n"));
    printf(("\n"));
  }
  else
  {
    Microseconds = User_Time * Mic_secs_Per_Second 
                        / (TimeFormat) Number_Of_Runs;
    Dhrystones_Per_Second = (TimeFormat) Number_Of_Runs / User_Time;
    Vax_Mips = Dhrystones_Per_Second / 1757.0;

#ifdef ROPT
    printf(("Register option selected?  YES\n"));
#else
    printf(("Register option selected?  NO\n"));
    strcpy(Reg_Define, "Register option not selected.");
#endif
    printf(("Microseconds for one run through Dhrystone: "));
    printf(("%7.1lf \n", Microseconds));
    printf(("Dhrystones per Second:                      "));
    printf(("%10.1lf \n", Dhrystones_Per_Second));
    printf(("VAX MIPS rating = %10.3lf \n",Vax_Mips));
    printf(("\n"));
  
#ifdef ENABLEFILEIO
  fprintf((Ap,"\n"));
  fprintf((Ap,"Dhrystone Benchmark, Version 2.1 (Language: C)\n"));
  fprintf((Ap,"%s\n",Reg_Define));
  fprintf((Ap,"Microseconds for one loop: %7.1lf\n",Microseconds));
  fprintf((Ap,"Dhrystones per second: %10.1lf\n",Dhrystones_Per_Second));
  fprintf((Ap,"VAX MIPS rating: %10.3lf\n",Vax_Mips));
  fclose(Ap);
#endif /* ENABLEFILEIO */
  }
  if (errors == 0)
    return(LXR_EXIT_SUCCESS);
  return(LXR_EXIT_FAILURE);
}

void
Proc_1 (Ptr_Val_Par)
/******************/

REG Rec_Pointer Ptr_Val_Par;
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */
  
  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp 
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */

void
Proc_2 (Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */

One_Fifty   *Int_Par_Ref;
{
  One_Fifty  Int_Loc;
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */

void
Proc_3 (Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */

Rec_Pointer *Ptr_Ref_Par;

{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */

void
Proc_4 () /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */

void
Proc_5 () /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */


        /* Procedure for the assignment of structures,          */
        /* if the C compiler doesn't support this feature       */
#ifdef  NOSTRUCTASSIGN
memcpy (d, s, l)
register char   *d;
register char   *s;
register int    l;
{
        while (l--) *d++ = *s++;
}
#endif
