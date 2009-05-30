#include "ccp4_fortran.h"
#include <stdio.h>

static void
bail(const char* function_name)
{
  fprintf(stderr, "FATAL ERROR: %s() not implemented.", function_name);
  exit(1);
}

#ifdef _MSC_VER
#if (CALL_LIKE_MVS==2)
int IARGC();
void GETARG(int *i, char *arg, int arg_len);
void CCP4H_INIT();
void CCP4H_INIT_LIB(int *ihtml, int *isumm);
void CCP4H_PRE_BEG();
void CCP4H_SUMMARY_BEG();
void CCP4H_SUMMARY_END();
#else
int __stdcall IARGC();
void __stdcall GETARG(int *i, char *arg, int arg_len);
void __stdcall CCP4H_INIT();
void __stdcall CCP4H_INIT_LIB(int *ihtml, int *isumm);
void __stdcall CCP4H_PRE_BEG();
void __stdcall CCP4H_SUMMARY_BEG();
void __stdcall CCP4H_SUMMARY_END();
#endif
#endif

FORTRAN_SUBR ( IARGC, iargc,
               (),
               (),
               ())
{ bail("FORTRAN iargc"); }

FORTRAN_SUBR ( GETARG, getarg,
               (int *i, char *arg, int arg_len),
               (int *i, char *arg, int arg_len),
               (int *i, char *arg, int arg_len))
{ bail("FORTRAN getarg"); }

FORTRAN_SUBR ( CCP4H_INIT, ccp4h_init,
               (),
               (),
               ())
{ bail("ccp4h_init"); }

FORTRAN_CALL ( CCP4H_INIT_LIB, ccp4h_init_lib,
               (int* ihtml, int* isumm),
               (int* ihtml, int* isumm),
               (int* ihtml, int* isumm))
{ bail("ccp4h_init_lib"); }

FORTRAN_SUBR ( CCP4H_PRE_BEG, ccp4h_pre_beg,
               (),
               (),
               ())
{ bail("ccp4h_pre_beg"); }

FORTRAN_SUBR ( CCP4H_SUMMARY_BEG, ccp4h_summary_beg,
               (),
               (),
               ())
{ bail("ccp4h_summary_beg"); }

FORTRAN_SUBR ( CCP4H_SUMMARY_END, ccp4h_summary_end,
               (),
               (),
               ())
{ bail("ccp4h_summary_end"); }
