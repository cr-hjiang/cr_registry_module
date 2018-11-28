#ifndef CR_PRINTER_H
#define CR_PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//function: print_debug
#ifndef NDEBUG_TEST
#ifndef print_debug
#define print_debug(fmt, ...) \
  do{ \
    printf("[DEBUG] " fmt "        @ %s:%d:%s()\n" , \
           __VA_ARGS__, __FILE__, __LINE__, __func__); \
  }while(0)
#endif //print_debug
#else
#ifndef print_debug
#define print_debug(fmt, ...) \
  do{}while(0)
#endif //print_debug
#endif //NDEBUG_TEST


void print_program_info(const char *prog_name, int header);

#endif //CR_PRINTER_H