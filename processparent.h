/*
 * process.h
 *
 *  Created on: May 12, 2023
 *      Author: user
 */

#ifndef PROCESSPARENT_H_
#define PROCESSPARENT_H_
#include <utility>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <chrono>
#include <thread>

#include "processchild.h"
#include "timeElapsed.h"
#include "utils.h"

class ProcessParent {
public:
  ProcessParent() = default;
  virtual ~ProcessParent();

  template<typename ThreadFunc, typename... Args>
  void start(ThreadFunc threadFunc, Args... args) {

    // initialize shared memory for parent
    shmid_ = sharedMemInit(sharedMemPageSize_);
    if (shmid_ < 0) {
      printf("unable to create shared mem. shmid: %d, errno: %s\n", shmid_, strerror(errno));
      return;
    }
    void *shm = sharedMemAttach(shmid_);
    if (isSharedMemValid(shm) == false) {
      printf("unable to attach shared mem. errno: %s\n", strerror(errno));
      sharedMemDeinit(shmid_);
      shmid_ = -1;
      return;
    }
    sharedMemParent_ = shm;
    //memset(sharedMemParent_, 0, sharedMemPageSize_);
    printf("shared mem parent: %p\n", sharedMemParent_);

    pid_ = fork();
    printf("fork result: 0x%.8X\n", pid_);
    if (pid_ == 0) {
      // child
      void *shm = sharedMemAttach(shmid_);
      if (isSharedMemValid(shm) == false) {
        printf("unable to attach shared mem in child. errno: %s. exiting child process\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      printf("shared mem child: %p\n", shm);
      ProcessChild processChild(shm, sharedMemPageSize_);

      // exec thread func
      int retval = threadFunc(args..., processChild);

      sharedMemDetach(shm);
      exit(retval);
    }
  }

  void stop() {
    if (pid_ < 0) {
      printf("child is already stopped\n");
      return;
    }
    requestStop();

    // wait for some time to complete the child process
    // then terminate if the child does not respond
    WaitProcessCompletionResult retval = waitProcessCompletion(pid_, timeoutCloseChildMs_);
    if (retval.first == WaitpidResult::Error ||
        retval.first == WaitpidResult::NormalExit ||
        retval.first == WaitpidResult::KilledBySignal) {
      pid_ = -1;
      freeSharedMemResources();
      return;
    }

    // child didn't answer on time. kill child forcibly
    // wait some time for exiting child by kill
    printf("killing 0x%.8X pid\n", pid_);
    int kill_retval = kill(pid_, SIGKILL);
    if (kill_retval == -1) {
      printf("kill returned status: %d. errno: %s\n", kill_retval, strerror(errno));
      pid_ = -1;
      freeSharedMemResources();
      return;
    }

    waitProcessCompletion(pid_, timeoutCloseChildMs_);
    printf("exiting stop\n");
    pid_ = -1;
    freeSharedMemResources();
  }



private:
  static constexpr size_t sharedMemPageSize_ = 4096;
  static constexpr uint32_t timeoutCloseChildMs_ = 2000;
  void requestStop();
  static int sharedMemInit(size_t pageSize);
  static void sharedMemDeinit(int shmid);
  static void *sharedMemAttach(int shmid);
  static void sharedMemDetach(void *sharedMem);
  static bool isSharedMemValid(const void *sharedMem);
  void freeSharedMemResources();


  //ThreadFunc threadFunc_;
  pid_t pid_ = -1;
  void *sharedMemParent_ = nullptr;
  int shmid_ = -1;
};

#endif /* PROCESSPARENT_H_ */
