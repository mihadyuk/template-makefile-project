/*
 * joinableThread.cpp
 *
 *  Created on: Mar 26, 2025
 *      Author: user
 */
#include <assert.h>
#include <stdio.h>
#include "joinableThread.h"



JoinableThread::JoinableThread() {
  // TODO Auto-generated constructor stub
}

JoinableThread::~JoinableThread() {
  // TODO Auto-generated destructor stub
  stop();
}

void JoinableThread::start() {
  if (isActive())
    return;
  printf("starting worker\n");
  thread_ = std::jthread(worker, std::ref(*this));
}

void JoinableThread::stop() {
  if (!isActive())
    return;
  bool res = thread_.request_stop();
  assert(res == true);
  thread_.join();
  printf("worker stopped\n");
}

void JoinableThread::worker(std::stop_token stoken, JoinableThread &self) {

  printf("worker started\n");
  while (stoken.stop_requested() == false) {
  //while (self.thread_.get_stop_token().stop_requested() == false) {
    printf("worker\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  printf("exiting worker\n");
}




