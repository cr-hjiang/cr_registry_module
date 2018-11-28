#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <my_global.h>
#include <mysql.h>

#include "BatchLoader.h"
#include "cr_printer.h"
#include "CrTimer.h"


using namespace std;

int main(int argc, char** argv) {
  print_program_info("Hello Corerain", 1);
  cout << "[CORERAIN] MySQL Version: " << mysql_get_client_info() << endl;
  MYSQL *con = mysql_init(NULL);
  cout << "[DEBUG] init done" << endl;

  if(con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if(mysql_real_connect(con, "localhost", "root", "1025", "registered_ppl", 0, NULL, 0) == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }
  cout << "任泉" << endl;

  if(mysql_query(con, "INSERT INTO ppl(reg_time, name) values('2018-01-02', '任泉')")) {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  mysql_close(con);
  return 0;
}
