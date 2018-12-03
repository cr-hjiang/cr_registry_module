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
    cout << "usage: " << argv[0]\
      << " " << "<registry folder root>"\
      << " " << "<my sql server IP>"\
      << " " << "<my sql account>"\
      << " " << "<my sql password>"\
      << " " << "<my sql database>"\
      << " " << "<my sql table>"\
      << endl;
    return -1;
  }
  string root_path = argv[1];
  string my_sql_server_ip = argv[2];
  string my_sql_account = argv[3];
  string my_sql_password = argv[4];
  string my_sql_db = argv[5];
  string my_sql_table = argv[6];
  //Init CrReg
  CrReg my_reg(root_path);

  //List to store all valid sub path in root path
  vector<string> path_list;
  //Collect sub path
  path_list = my_reg.collect_data_path();

  //Init a MYSQL
  MYSQL *my_sql = mysql_init(NULL);
  //Connect to the database that used to stroe info
  mysql_real_connect(my_sql, my_sql_server_ip.c_str(),\
                     my_sql_account.c_str(), my_sql_password.c_str(),\
                     my_sql_db.c_str(), 0, NULL, 0);
  //Suchpport Chinese
  mysql_query(my_sql, "SET NAMES UTF8");
  ////Choose the tabel
  //string use_db = "USE " + my_sql_db;
  //int verify = mysql_query(my_sql, use_db.c_str());
  int counter = 0;

  //Loop through the sub_path list and register all data to the table
  while(!path_list.empty()) {
    vector<string> ppl_info = my_reg.collect_info(path_list.front());
    string my_query = "INSERT INTO " + my_sql_table +\
      (string) " (reg_time,name,gender," +\
      (string) "date_of_birth,id_num,img_path_1,img_path_2," +\
      (string) "img_path_3,img_path_4,img_path_5) VALUES (";
    for(int i = 0; i < ppl_info.size(); i++) {
      if(ppl_info[i].compare("") == 0) {
        my_query = my_query + "NULL,";
      } else {
        my_query = my_query + "'" + ppl_info[i] + "',";
      }
    }
    my_query = my_query.substr(0, my_query.length() -1) + ")";
    int verify = mysql_query(my_sql, my_query.c_str());
    if(verify == 0) {
      cout << "[CORERAIN] Insertion succeeds" << endl;
    } else {
      cout << "[CORERAIN] Insertion fails" << endl;
    }
    path_list.erase(path_list.begin());
    counter++;
  }

  //Close my_sql
  mysql_close(my_sql);
  cout << "[CORERAIN] Total people number: " << counter << endl;
  return 0;
}
