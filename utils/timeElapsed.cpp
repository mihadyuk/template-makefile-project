/*
 * timeElapsed.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: user
 */

#include "timeElapsed.h"

TimeElapsed::TimeElapsed() {
  //start();
}

TimeElapsed::~TimeElapsed() {
}

void TimeElapsed::start() {
  m_timeStamp = std::chrono::steady_clock::now();
}

double TimeElapsed::elapsed() {
  return std::chrono::duration<double>(std::chrono::steady_clock::now() - m_timeStamp).count();
}
