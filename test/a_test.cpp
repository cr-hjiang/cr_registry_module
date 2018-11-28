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
  CrTimer a_timer;
  cv::Mat img_512;
  cv::Mat img_256;
  cv::Mat *dst_512;
  cv::Mat *dst_256;
  vector<uchar> buf_512;
  vector<uchar> buf_256;

  cv::Mat img = cv::imread("../data/hello.jpg");
  cv::resize(img, img_512, cv::Size(512, 512));
  cv::resize(img, img_256, cv::Size(256, 256));

  a_timer.get_start_time();
  cv::imencode(".jpg", img_512, buf_512);
  a_timer.get_end_time("512 encode");

  cout << buf_512.size() << endl;

  a_timer.get_start_time();
  cv::imdecode(buf_512, 1, dst_512);
  a_timer.get_end_time("512 decode");

  a_timer.get_start_time();
  cv::imencode(".jpg", img_256, buf_256);
  a_timer.get_end_time("256 encode");

  cout << buf_256.size() << endl;

  a_timer.get_start_time();
  cv::imdecode(buf_256, 1, dst_256);
  a_timer.get_end_time("256 decode");
  return 0;
}
