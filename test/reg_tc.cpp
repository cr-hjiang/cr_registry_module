#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#define int64 opencv_broken_int
#define uint64 opencv_broken_uint
#include <opencv2/opencv.hpp>
#undef int64
#undef uint64

#include <ctime>
#include <my_global.h>
#include <mysql.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "CrReg.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
  if(argc < 2) {
    cout << "usage: " << argv[0] \
      << " " << "<registry folder root>" \
      << endl;
    return -1;
  }
  string root_path = argv[1];
  CrReg my_reg(root_path);

  vector<string> path_list;
  path_list = my_reg.collect_data_path();

  MYSQL *my_sql = mysql_init(NULL);

  mysql_real_connect(my_sql, "localhost", "joshtrick", "1025", NULL, 0, NULL, 0);
  mysql_query(my_sql, "SET NAMES UTF8");
  int verify = mysql_query(my_sql, "USE registered_ppl");
  cout << verify << endl;
  int counter = 0;
  while(!path_list.empty()) {
    vector<string> ppl_info = my_reg.collect_info(path_list.front());
    string my_query = "INSERT INTO ppl (reg_time,name,gender,"\
      + (string) "date_of_birth,id_num,img_path_1,img_path_2,"\
      + (string) "img_path_3,img_path_4,img_path_5) VALUES (";
    for(int i = 0; i < ppl_info.size(); i++) {
      if(ppl_info[i].compare("") == 0) {
        my_query = my_query + "NULL,";
      } else {
        my_query = my_query + "'" + ppl_info[i] + "',";
      }
    }
    my_query = my_query.substr(0, my_query.length() -1) + ")";
    //cout << my_query << endl;
    int verify = mysql_query(my_sql, my_query.c_str());
    if(verify == 0) {
      cout << "[CORERAIN] Insertion succeeds" << endl;
    } else {
      cout << "[CORERAIN] Insertion fails" << endl;
    }
    path_list.erase(path_list.begin());
    counter++;
  }
  mysql_close(my_sql);
  cout << "[CORERAIN] Total people number: " << counter << endl;
  return 0;
}
