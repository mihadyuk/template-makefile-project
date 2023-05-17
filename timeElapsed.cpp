/*
 * timeElapsed.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: user
 */

#include "timeElapsed.h"

using namespace std::chrono;

TimeElapsed::TimeElapsed() {
  start();
}

TimeElapsed::~TimeElapsed() {
}

void TimeElapsed::start() {
#if defined(USE_STEADY_CLOCK)
  m_timeStamp = steady_clock::now();
#elif defined(USE_GETTIMEOFDAY)
  gettimeofday(&m_timeStamp, NULL);
#else
  m_timeStamp = high_resolution_clock::now();
#endif
}

uint64_t TimeElapsed::elapsedMicroseconds() {
#if defined(USE_GETTIMEOFDAY)
  return (uint64_t)elapsed();
#else
  return (uint64_t)(elapsed() * 1e6 + 0.5);
#endif
}

bool TimeElapsed::isElapsedMicroseconds(uint64_t microseconds) {
#if defined(USE_GETTIMEOFDAY)
  uint64_t elapsedMicroseconds = (uint64_t)elapsed();
#else
  uint64_t elapsedMicroseconds = (uint64_t)(elapsed() * 1e6 + 0.5f);
#endif
  if (elapsedMicroseconds >= microseconds)
    return true;
  return false;
}

bool TimeElapsed::isElapsedMilliseconds(uint64_t milliseconds) {
#if defined (USE_GETTIMEOFDAY)
  uint64_t elapsedMs = (uint64_t)(elapsed() * 1e-3 + 0.5f);
#else
  uint64_t elapsedMs = (uint64_t)(elapsed() * 1e3 + 0.5f);
#endif
  if (elapsedMs >= milliseconds)
    return true;
  return false;
}

uint64_t TimeElapsed::elapsedMilliseconds() {
#if defined (USE_GETTIMEOFDAY)
  return (uint64_t)(elapsed() * 1e-3 + 0.5);
#else
  return (uint64_t)(elapsed() * 1e3 + 0.5);
#endif
}

double TimeElapsed::elapsed() {
#if defined (USE_STEADY_CLOCK)
  steady_clock::time_point timeNow = steady_clock::now();
  duration<double>timeSpan = duration_cast<duration<double>>(timeNow - m_timeStamp);
  return timeSpan.count();
#elif defined(USE_GETTIMEOFDAY)
  timeval time_now;
  gettimeofday(&time_now, NULL);
  double elapsedTime = (time_now.tv_sec - m_timeStamp.tv_sec) * 1000000ULL;
  elapsedTime += (time_now.tv_usec - m_timeStamp.tv_usec);
  return elapsedTime;
#else
  high_resolution_clock::time_point timeNow = high_resolution_clock::now();
  duration<double>timeSpan = duration_cast<duration<double>>(timeNow - m_timeStamp);
  return timeSpan.count();
#endif
}
