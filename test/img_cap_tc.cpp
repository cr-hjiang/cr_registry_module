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

  VideoCapture cap;
  CrImgCap my_cap(root_path.c_str());
  //Make img directory
  if(my_cap.mk_path(my_cap.root_path) != 0) {
    exit(0);
  };

  while(!my_cap.reg_finished) {
    string name = "";
    string gender = "";
    string dob = "";
    string ID_num = "";


    my_cap.set_ppl_info(name, gender, dob, ID_num);
    my_cap.write_ppl_info(name, gender, dob, ID_num);

    if(!cap.open(0)) {
      return 0;
    }
    
    Mat frame;
    cap >> frame;
    int h = frame.size().height;
    int w = frame.size().width;
    int n_h = 550;
    int n_w = 550;
    int p1_h = (h-n_h)/2;
    int p1_w = (w-n_w)/2;
    int img_nu = 0;
    while(img_nu < 5) {
      cap >> frame;
      Mat crop_frame(frame, Rect(p1_w, p1_h, n_w, n_h));
      Mat mirror_frame;
      flip(crop_frame, mirror_frame, 1);
      imshow("This is you, smile! :)", mirror_frame);
      if(waitKey(100) == 13) {
        imshow("This is you, smile! :)", mirror_frame);
        cout << "[CORERAIN] Save this photo? (press ENTER to save or other keys to cancel)" << endl;
        if(waitKey(0) == 13) {
          string img_name = my_cap.sub_path + "img_" + to_string(img_nu) + ".jpg";
          imwrite(img_name, crop_frame);
          img_nu++;
        }
      }
    }
    char finished_tmp;
    cout << "[CORERAIN] Another registry? (y or n): ";
    cin >> finished_tmp;
    if(finished_tmp == 'n') {
      my_cap.reg_finished = true;
    }
  }
  cap.release();

  return 0;
}
