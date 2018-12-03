#include "CrReg.h"

using namespace std;
using namespace cv;

//Constructor
//path - root path of the ready-to-use persons data Set
CrReg::CrReg(string path) {
  struct stat info;
  if(stat(path.c_str(), &info) != 0) {
    cout << "[CORERAIN] No Such directory: " << path << endl;
    exit(-1);
  } else {
    int loc = path.find_last_of("/\\");
    if(loc+1 != path.length()) {
      path = path + "/";
    }
    this->root_path = path;
    cout << "[CORERAIN] Data path selected: " << root_path << endl;
  }
}

//Destructor
CrReg::~CrReg() {
}

//Check if sub_path is valid (with a info.txt in it).
bool CrReg::info_exist(string sub_path) {
  string file_name = sub_path+"info.txt";
  ifstream in_file(file_name.c_str());
  return (bool) in_file;
}

//Collect a sub path and add it to a path list
vector<string> CrReg::collect_data_path() {
  vector<string> sub_path_list;
  struct dirent *sub_dir_entry;
  DIR *root_dir = opendir(this->root_path.c_str());
  DIR *sub_dir;
  while((sub_dir_entry = readdir(root_dir)) != NULL) {
    string sub_path = this->root_path + sub_dir_entry->d_name + "/";
    if((sub_dir = opendir(sub_path.c_str())) != NULL) {
      if(info_exist(sub_path)) {
        sub_path_list.push_back(sub_path);
      }
    }
  }
  closedir(root_dir);
  closedir(sub_dir);
  return sub_path_list;
}

//Collect info from a sub path(data_path)
vector<string> CrReg::collect_info(string data_path) {
  vector<string> out_info;
  int loc = data_path.find_last_of("/\\");
  if(loc+1 != data_path.length()) {
    data_path = data_path + "/";
  }

  time_t     now = time(0);
  struct tm  tstruct;
  char       time_buf[20];
  tstruct = *localtime(&now);
  strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %X", &tstruct);

  this->reg_time = time_buf;
  out_info.push_back(this->reg_time);

    this->ppl_info.erase(ppl_info.begin(), ppl_info.end());
    this->img_path_list.erase(img_path_list.begin(), img_path_list.end());
  string file_name = data_path+"info.txt";

  try {
    ifstream in_file(file_name.c_str());
    for(int i = 0; i < 4; i++) {
      string line = "";
      getline(in_file, line);
      ppl_info.push_back(line);
      out_info.push_back(this->ppl_info[i]);
    }
    in_file.close();
    for(int i = 0; i < 5; i++) {
      string img_path = data_path + "img_" + to_string(i) + ".jpg";
      Mat img = imread(img_path);
      if(img.data == NULL) {
        this->img_path_list.push_back("");
      } else {
        this->img_path_list.push_back(img_path);
      }
      out_info.push_back(this->img_path_list[i]);
    }
  }  catch(...) {
    out_info.erase(out_info.begin(), out_info.end());
    cout << "[CORERAIN] Bad Info." << endl;
  }
  return out_info;
}

