#ifndef CRIMGCAP_H
#define CRIMGCAP_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>

class CrImgCap {
public:
  CrImgCap(const char* path);
  ~CrImgCap();
  bool reg_finished;
  std::string sub_path;
  const char* root_path;
  
  int mk_path(const char* path);
  void set_ppl_info(std::string &name, std::string &gender, std::string &dob, std::string &ID_num);
  void write_ppl_info(std::string &name, std::string &gender, std::string &dob, std::string &ID_num);
private:
  cv::VideoCapture cap;
};


#endif //CRIMGCAP_H
