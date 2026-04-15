/*
 * timeElapsed.h
 *
 *  Created on: Jun 8, 2015
 *      Author: user
 */

#ifndef TIMEELAPSED_H_
#define TIMEELAPSED_H_
#include <chrono>

class TimeElapsed {
public:
  TimeElapsed();
  virtual ~TimeElapsed();
  void start();
  std::chrono::milliseconds elapsedMs();
private:
  std::chrono::steady_clock::time_point timeStamp_;
};

#endif //TIMEELAPSED_H_
