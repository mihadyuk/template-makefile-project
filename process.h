/*
 * process.h
 *
 *  Created on: May 12, 2023
 *      Author: user
 */

#ifndef PROCESS_H_
#define PROCESS_H_
#include <utility>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

template<typename ThreadFunc, typename... Args>
class Process {
public:
  Process()
  {
  }
  virtual ~Process() {}

  void start(ThreadFunc threadFunc, Args... args) {
    threadFunc_ = threadFunc;

    pid_ = fork();
    printf("fork result: 0x%.8X\n", pid_);
    if (pid_ == 0) {
      // child
      int retval = threadFunc_(args...);
      exit(retval);
    }
  }

  void stop() {
    printf("killing 0x%.8X pid\n", pid_);
    int retval = kill(pid_, SIGKILL);
    printf("kill returned status: %d\n", retval);
    int status = 0;
    pid_t waitpid_retval = waitpid(pid_, &status, 0);
    printf("waitpid_retval: 0x%.8X, status: 0x%.8X\n", waitpid_retval, status);
  }
private:
  ThreadFunc threadFunc_;
  pid_t pid_ = -1;
};

#endif /* PROCESS_H_ */
