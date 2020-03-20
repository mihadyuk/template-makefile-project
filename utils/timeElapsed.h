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
  ~TimeElapsed();
  void start();
  double elapsed();
private:
  std::chrono::time_point<std::chrono::steady_clock> m_timeStamp;
};

#endif /* TIMEELAPSED_H_ */
