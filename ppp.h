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


class PPP {
public:
  PPP();
  virtual ~PPP();

  void start();
  void stop();

private:
  void threadFunc();
  std::string buildPppParams();

  int pipe_stdout_[2];
  int pipe_stderr_[2];
  std::thread thread_;
  std::atomic_bool stop_;
  pid_t pid_ = -1;
};



#endif /* PPP_H_ */
