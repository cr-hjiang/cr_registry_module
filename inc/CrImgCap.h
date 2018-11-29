#ifndef CRIMGCAP_H
#define CRIMGCAP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <opencv2/opencv.hpp>

class CrImgCap {
public:
  CrImgCap(std::string path);
  ~CrImgCap();
  bool reg_finished;
  std::string sub_path;
  std::string root_path;
  cv::VideoCapture cap;

  int mk_path(std::string path);
  void set_ppl_info();
  void write_ppl_info();
  void img_cap();
private:
  std::string name = "";
  std::string gender = "";
  std::string dob = "";
  std::string ID_num = "";
};


#endif //CRIMGCAP_H
