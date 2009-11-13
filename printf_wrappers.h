#ifndef CCP4IO_ADAPTBX_PRINTF_WRAPPERS_H
#define CCP4IO_ADAPTBX_PRINTF_WRAPPERS_H

#include <stdio.h>

extern int ccp4io_printf_mode;

int
ccp4io_printf(
  const char* format,
  ...)
;

int
ccp4io_fprintf(
  FILE* stream,
  const char* format,
  ...)
;

#endif /* GUARD */
