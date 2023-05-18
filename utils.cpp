/*
 * utils.cpp
 *
 *  Created on: May 18, 2023
 *      Author: user
 */
#include <stdio.h>
#include <string.h>
#include <thread>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"
#include "timeElapsed.h"

WaitProcessCompletionResult waitProcessCompletion(pid_t pid, uint32_t timeoutMs) {

  TimeElapsed timeElapsed;
  timeElapsed.start();
  while (timeElapsed.isElapsedMilliseconds(timeoutMs) == false) {
    int status = 0;
    pid_t retval = waitpid(pid, &status, WNOHANG);
    if (retval == -1) {
      printf("waitpid returned -1 for process 0x%.8X. errno: %s\n", pid, strerror(errno));
      return WaitProcessCompletionResult(WaitpidResult::Error, std::optional<int>());
    }
    else if (retval == pid) {
      if (WIFEXITED(status)) {
        printf("process 0x%.8X normally exited with code %d. status: 0x%.8X\n", pid, WEXITSTATUS(status), status);
        return WaitProcessCompletionResult(WaitpidResult::NormalExit, status);
      }
      else if (WIFSIGNALED(status)) {
        printf("process 0x%.8X killed by signal %d. status: 0x%.8X\n", pid, WTERMSIG(status), status);
        return WaitProcessCompletionResult(WaitpidResult::KilledBySignal, status);
      }
    }
    //printf("child status is not changed. retval: 0x%.8X\n", retval);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return WaitProcessCompletionResult(WaitpidResult::Timeout, std::optional<int>());
}


