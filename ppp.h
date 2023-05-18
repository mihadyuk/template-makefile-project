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
  static int threadFuncStdStreams(PPP &self, ProcessChild &processChild);
  static int threadFuncPpp(PPP &self, ProcessChild &processChild);
  std::string buildPppParams();

  ProcessParent procStdStreams_;
  ProcessParent procPpp_;
  int pipe_stdout_[2];
  int pipe_stderr_[2];
};



#endif /* PPP_H_ */
