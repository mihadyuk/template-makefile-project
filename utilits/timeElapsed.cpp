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
  timeStamp_ = steady_clock::now();
}


std::chrono::milliseconds TimeElapsed::elapsedMs() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now() - timeStamp_);
}
