/*
 * ppp.h
 *
 *  Created on: May 12, 2023
 *      Author: user
 */

#ifndef PPP_H_
#define PPP_H_

#include <atomic>
#include <string>
#include <thread>

#include "processparent.h"


class PPP {
public:
  PPP();
  virtual ~PPP();

  void start();
  void stop();

private:
  static int threadFunc(ProcessChild &processChild, PPP &self);
  std::string buildPppParams();

  ProcessParent process_;
  int pipe_stdout_[2];
  int pipe_stderr_[2];
  std::atomic_bool stop_;
  pid_t pid_ = -1;
};



#endif /* PPP_H_ */
