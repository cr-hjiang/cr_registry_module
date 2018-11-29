#ifndef CRREG_H
#define CRREG_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

class CrReg {
public:
  CrReg(std::string path);
  ~CrReg();
  bool info_exist(std::string sub_path);
  std::vector<std::string> collect_data_path();
  std::vector<std::string> collect_info(std::string data_path);
private:
  std::string root_path;
  std::string reg_time;
  std::vector<std::string> ppl_info;
  std::vector<std::string> img_path_list;
};


#endif //CRREG_H
