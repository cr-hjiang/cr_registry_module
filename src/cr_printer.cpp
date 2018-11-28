#include "cr_printer.h"

using namespace std;

void print_program_info(const char *prog_name, int header) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int line_len = 71;
  int str_len = strlen(prog_name);
  int str_count = (str_len % line_len == 0 ? str_len : str_len - str_len % line_len + line_len);


  printf("------------------------------------CORERAIN TECHNOLOGIES------------------------------------\n");
  if(header) {
    printf("|  ####    ####    #####    #####  #####     ###   ##  ##  #                                |\n");
    printf("| ##      ##  ##   ##  ##   ##     ##   ##  #####  ##  ##  #                                |\n");
    printf("|##      ##    ##  ##  ##   ####   ##   ##  #  ##  ##  ### #                                |\n");
    printf("|##      ##    ##  #####    ##     #####    #  ##  ##  #####                                |\n");
    printf("|##      ##    ##  ## ##    ##     ## ##    #####  ##  # ###                                |\n");
    printf("| ##      ##  ##   ##  ##   ##     ##  ##   #  ##  ##  #  ##                                |\n");
    printf("|  ####    ####    ##  ###  #####  ##  ###  #  ##  ##  #   #                                |\n");
    printf("|                                                                                           |\n");
    printf("|######  #####    ####  ##   ##  ##  #    ####    ##       ####      ####   ##  #####   ####|\n");
    printf("|  ##    ##      ##     ##   ##  ##  #   ##  ##   ##      ##  ##    ##      ##  ##     ##   |\n");
    printf("|  ##    ####   ##      ##   ##  ### #  ##    ##  ##     ##    ##  ##       ##  ####   ###  |\n");
    printf("|  ##    ##     ##      #######  #####  ##    ##  ##     ##    ##  ##  ##   ##  ##      ### |\n");
    printf("|  ##    ##     ##      ##   ##  # ###  ##    ##  ##     ##    ##  ##   ##  ##  ##       ###|\n");
    printf("|  ##    ##      ##     ##   ##  #  ##   ##  ##   ##      ##  ##    ##  ##  ##  ##        ##|\n");
    printf("|  ##    #####    ####  ##   ##  #   #    ####    #####    ####      #####  ##  #####  #### |\n");
    printf("|                                                                                           |\n");
  }

  printf("|[CORERAIN] Date:    %02d/%02d/%04d                                                             |\n",
         tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  printf("|[CORERAIN] Time:    %02d:%02d:%02d                                                               |\n",
         tm.tm_hour, tm.tm_min, tm.tm_sec);

  printf("|[CORERAIN] Program: ");
  for(int i = 0; i < str_count; i++) {
    if((i+1)%line_len == 0 && i != str_count - 1) {
      printf("%c|\n", prog_name[i]);
    }else if((i+1)%line_len == 1 && i != 0) {
      printf("|                    %c", prog_name[i]);
    }else if(i < str_len) {
      printf("%c", prog_name[i]);
      if(i == str_count - 1) {
        printf("|\n");
      }
    }else {
      printf(" ");
      if(i == str_count - 1) {
        printf("|\n");
      }
    }
  }
  printf("------------------------------------CORERAIN TECHNOLOGIES------------------------------------\n");
  printf("\n");
}
