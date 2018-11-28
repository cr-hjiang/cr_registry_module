#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "BatchLoader.h"
#include "cr_printer.h"
#include "CrTimer.h"

using namespace std;

int main() {
  print_program_info("Hello Corerain", 1);

  vector<cv::Mat> img;
  vector<cv::String> name;
  vector<cv::String> path;
  BatchLoader loader("/Users/joshtrick/j_codes/cr_registry_module/data/", true);
  CrTimer a_timer;

  a_timer.get_start_time();
  loader.load(img, path, name);
  a_timer.get_end_time();

  a_timer.get_start_time();
  loader.save(img, path, name);
  a_timer.get_end_time();
  return 0;
}
