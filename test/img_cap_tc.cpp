#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <my_global.h>
#include <mysql.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "CrImgCap.h"

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



  CrImgCap my_cap(root_path.c_str());

  //Make img directory
  if(my_cap.mk_path(my_cap.root_path) != 0) {
    exit(0);
  };

  while(!my_cap.reg_finished) {

    my_cap.set_ppl_info();
    my_cap.write_ppl_info();
    my_cap.img_cap();

  }
  my_cap.cap.release();

  return 0;
}
