#ifndef BATCHLOADER_H
#define BATCHLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class BatchLoader {
public:
  BatchLoader(std::string input_path, bool recursion);
  ~BatchLoader();
  void set_path(std::string path, bool recursion);
  void get_path();
  void load(std::vector<cv::Mat> &img_buf, std::vector<cv::String> &img_path, std::vector<cv::String> &img_name);
  void save(std::vector<cv::Mat> &img_buf, std::vector<cv::String> &img_path, std::vector<cv::String> &img_name);
private:
  std::string loading_path;
  bool dir_recursion;
};



#endif //BATCHLOADER_H
