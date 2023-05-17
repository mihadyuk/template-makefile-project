/*
 * timeElapsed.h
 *
 *  Created on: Jun 8, 2015
 *      Author: user
 */

#ifndef TIMEELAPSED_H_
#define TIMEELAPSED_H_
#include <stdint.h>
#include <chrono>
#include <sys/time.h>

#define USE_STEADY_CLOCK
//#define USE_GETTIMEOFDAY

//using namespace std::chrono;

class TimeElapsed {
public:
  TimeElapsed();
  virtual ~TimeElapsed();
  void start();
  bool isElapsedMicroseconds(uint64_t microseconds);
  uint64_t elapsedMicroseconds();
  bool isElapsedMilliseconds(uint64_t milliseconds);
  uint64_t elapsedMilliseconds();
  double elapsed();
private:
#if defined (USE_STEADY_CLOCK)
  std::chrono::steady_clock::time_point m_timeStamp;
#elif defined (USE_GETTIMEOFDAY)
  timeval m_timeStamp;
#else
  std::chrono::high_resolution_clock::time_point m_timeStamp;
#endif


};

#if defined(USE_GETTIMEOFDAY)
#error "gettimeofday is obsolete. Rework code to use clock_gettime instead. \
       Besides the elapsed function possibly contains errors. Use timersub macro to calc diff time."
#endif
#endif /* TIMEELAPSED_H_ */
