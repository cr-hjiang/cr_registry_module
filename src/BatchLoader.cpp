#include "BatchLoader.h"
using namespace std;

BatchLoader::BatchLoader(string input_path, bool recursion) {
  loading_path = input_path;
  dir_recursion = recursion;
}
BatchLoader::~BatchLoader() {
}

void BatchLoader::set_path(string path, bool recursion) {
  loading_path = path;
  dir_recursion = recursion;
}

void BatchLoader::get_path() {
  cout << "[CORERAIN] Loading path ";
  if(dir_recursion == true) {
    cout << "(recursive): ";
  } else {
    cout << "(non-recursive): ";
  }
  cout << loading_path << endl;
}

void BatchLoader::load(vector<cv::Mat> &img_buf, vector<cv::String> &img_path, vector<cv::String> &img_name) {
  cv::String img_root(loading_path);
  cv::glob(img_root, img_name, dir_recursion);
  int list_size = img_name.size();
  int dyn_idx = 0;

  //Try to load valid images based on image name list
  for(int i = 0; i < list_size; i++) {
    cv::Mat tmp_img = cv::imread(img_name[dyn_idx]);
    if(tmp_img.empty()) {
      img_name.erase(img_name.begin()+dyn_idx);
    } else {
      int loc = img_name[dyn_idx].find_last_of("/\\");
      if(loc != img_name[dyn_idx].npos) {
        cv::String tmp_name = img_name[dyn_idx].substr(loc+1);
        cv::String tmp_path = img_name[dyn_idx].substr(0, loc+1);
        img_name[dyn_idx].clear();
        img_name[dyn_idx] = tmp_name;
        img_path.push_back(tmp_path);
      } else {
        img_path.push_back("");
      }
      img_buf.push_back(tmp_img);
      dyn_idx++;
    }
  }
}

void BatchLoader::save(vector<cv::Mat> &img_buf, vector<cv::String> &img_path, vector<cv::String> &img_name) {
  if(img_buf.size() == img_path.size() && img_buf.size() == img_name.size()) {
    for(int i = 0; i < img_buf.size(); i++) {
      cv::String tmp_path = img_path[i] + "(CR_" + to_string(i) + ")" + img_name[i];
      cv::imwrite(tmp_path, img_buf[i]);
    }
  } else {
    cout << "[CORERAIN] Size of img_buf, img_path and img_name must be identical." << endl;
  }
}
