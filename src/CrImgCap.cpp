#include "CrImgCap.h"

using namespace std;
using namespace cv;

CrImgCap::CrImgCap(string path) {
  root_path = path;
  reg_finished = false;
  if(!cap.open(0)) {
    cout << "[CORERAIN] Camera not working" << endl;
    exit(0);
  }
}
CrImgCap::~CrImgCap() {
}

int CrImgCap::mk_path(string path) {
  struct stat info;
  if(stat(path.c_str(), &info) != 0) {
    if(mkdir(path.c_str(), 0777) != 0) {
      cout << "[CORERAIN] Error to make directory" << path << endl;
      return(-1);
    } else {
      return (0);
    }
  } else if(info.st_mode & S_IFDIR ) {
    cout << "[CORERAIN] Directory named " << path << " exists." << endl;
    char dtm_tmp;
    while(1) {
      cout << "[CORERAIN] Are you sure to use it? (y or n): ";
      cin >> dtm_tmp;
      if(dtm_tmp == 'n') {
        return(-1);
      } else if(dtm_tmp == 'y') {
        return(0);
      }
    }
  } else {
    cout << "[CORERAIN] File named " << path << " exists." << endl;
    return(-1);
  }
}


void CrImgCap::set_ppl_info() {
  bool finished = false;
  int option;
  name = "";
  gender = "";
  dob = "";
  ID_num = "";

  while(!finished) {
    cout << endl;
    cout << "[CORERAIN] Input options:" << endl;
    cout << "[CORERAIN] [1] Finish [2] Print Info.   [3] Name" << endl;
    cout << "[CORERAIN] [4] Gender [5] Date of Birth [6] ID Number" << endl;
    cout << "[CORERAIN] Choose an option (1-6) to input (1 to finish): ";
    string option_tmp;
    cin >> option_tmp;
    if(option_tmp.compare("0") < 0 || option_tmp.compare("9") > 0) {
      cout << "[CORERAIN] Invalid option, try again." << endl;
      continue;
    }
    option = atoi(option_tmp.c_str());
    switch(option) {
    case 1: {
              finished = true;
              cout << "[CORERAIN] Information Complete" << endl;
            } break;

    case 2: {
              cout << "[CORERAIN] Name:          " << name << endl;
              cout << "[CORERAIN] Gender:        " << gender << endl;
              cout << "[CORERAIN] Date of Birth: " << dob << endl;
              cout << "[CORERAIN] ID Number:     " << ID_num << endl;
            } break;

    case 3: {
              string name_tmp;
              cout << "[CORERAIN] Input name (or type q to quit): ";
              cin.ignore(INT_MAX, '\n');
              getline(cin, name_tmp);
              if(name_tmp.compare("q") == 0) {
                cout << "[CORERAIN] Quit" << endl;
              } else {
                name = name_tmp;
              }
            } break;

    case 4: {
              bool gender_success = true;
              string gender_tmp;
              do {
                cout << "[CORERAIN] Input gender (m for male, f for female or q to quit): ";
                gender_success = true;
                cin >> gender_tmp;
                if(gender_tmp.compare("m") == 0 || gender_tmp.compare("f") == 0) {
                  gender = gender_tmp;
                } else if(gender_tmp.compare("q") == 0) {
                  cout << "[CORERAIN] Quit" << endl;
                } else {
                  gender_success = false;
                  cout << "[CORERAIN] Invalid setting, try again." << endl;
                }
              } while(!gender_success);
            } break;

    case 5: {
              bool dob_success = true;
              string dob_tmp;
              do {
                dob_success = true;
                cout << "[CORERAIN] Input date of birth (YYYY-MM-DD or q to quit): ";
                cin >> dob_tmp;

                if(dob_tmp.length() == 10 && dob_tmp[4] == dob_tmp[7] && dob_tmp[4] == '-') {
                  int y_tmp;
                  int m_tmp;
                  int d_tmp;
                  try {
                    y_tmp = stoi(dob_tmp.substr(0,4));
                    m_tmp = stoi(dob_tmp.substr(5,7));
                    d_tmp = stoi(dob_tmp.substr(8));
                  } catch(...) {
                    cout << "[CORERAIN] Invalid setting, try again." << endl;
                    dob_success = false;
                  }
                  switch(m_tmp) {
                  case 1:
                  case 3:
                  case 5:
                  case 7:
                  case 8:
                  case 10:
                  case 12: {
                             if(d_tmp <= 31 && d_tmp >= 1) {
                               dob = dob_tmp;
                             } else {
                               dob_success = false;
                               cout << "[CORERAIN] Invalid setting, try again." << endl;
                             }
                           } break;

                  case 4:
                  case 6:
                  case 9:
                  case 11: {
                             if(d_tmp <= 30 && d_tmp >= 1) {
                               dob = dob_tmp;
                             } else {
                               dob_success = false;
                               cout << "[CORERAIN] Invalid setting, try again." << endl;
                             }
                           } break;

                  case 2: {
                            if(y_tmp%4 == 0 && d_tmp <= 29 && d_tmp >= 1) {
                              dob = dob_tmp;
                            } else if(y_tmp%4 != 0 && d_tmp <= 28 && d_tmp >= 1) {
                              dob = dob_tmp;
                            } else {
                              dob_success = false;
                              cout << "[CORERAIN] Invalid setting, try again." << endl;
                            }
                          } break;

                  default: {
                             dob_success = false;
                             cout << "[CORERAIN] Invalid setting, try again." << endl;
                           } break;
                  }

                } else if(dob_tmp.compare("q") == 0) {
                  cout << "[CORERAIN] Quit" << endl;
                } else {
                  dob_success = false;
                  cout << "[CORERAIN] Invalid setting, try again." << endl;
                }
              } while(!dob_success);
            } break;

    case 6: {
              bool ID_num_success = true;
              string ID_num_tmp;
              do {
                cout << "[CORERAIN] Input ID number (18-Bits): ";
                ID_num_success = true;
                cin >> ID_num_tmp;
                if(ID_num_tmp.length() == 18) {
                  ID_num = ID_num_tmp;
                } else if(ID_num_tmp.compare("q") == 0) {
                  cout << "[CORERAIN] Quit" << endl;
                } else {
                  ID_num_success = false;
                  cout << "[CORERAIN] Invalid setting, try again." << endl;
                }
              } while(!ID_num_success);
            } break;
    default: {
               cout << "[CORERAIN] Invalid option, try again." << endl;
             } break;
    }
  }
}

void CrImgCap::write_ppl_info() {
  string root_path_tmp = root_path;
  time_t now = time(0);
  sub_path = to_string(now)+ "_" + name +"/";
  int loc = root_path_tmp.find_last_of("/\\");
  if(loc+1 != root_path_tmp.length()) {
    root_path_tmp += "/";
  }
  sub_path = root_path_tmp+sub_path;

  this->mk_path(sub_path.c_str());
  string file_name = sub_path + "info.txt";
  ofstream my_file;
  my_file.open(file_name);
  my_file << name << "\n" << gender << "\n" << dob << "\n" << ID_num;
  my_file.close();
}

void CrImgCap::img_cap() {
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
    imshow("Corerain Registry", mirror_frame);
    if(waitKey(100) == 13) {
      imshow("Corerain Registry", mirror_frame);
      cout << "[CORERAIN] Save this photo? (press ENTER to save or other keys to cancel)" << endl;
      if(waitKey(0) == 13) {
        string img_name = sub_path + "img_" + to_string(img_nu) + ".jpg";
        imwrite(img_name, crop_frame);
        img_nu++;
      }
    }
  }
  char finished_tmp;
  cout << "[CORERAIN] Another registry? (y or n): ";
  cin >> finished_tmp;
  if(finished_tmp == 'n') {
    reg_finished = true;
  }
}
