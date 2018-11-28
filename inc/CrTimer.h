#ifndef CRTIMER_H
#define CRTIMER_H

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <time.h>

class CrTimer {
public:
  CrTimer();
  ~CrTimer();
  void get_start_time();
  float get_end_time(std::string proc_name = "Execution");
private:
  long time_ms, time_us, time_ns, dt_ns;
  time_t time_s, dt_s;
  float time;
  timespec t_start, t_end;
};


#endif //CRTIMER_H
