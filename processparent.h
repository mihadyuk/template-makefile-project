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

class ProcessParent {
public:
  ProcessParent() = default;
  virtual ~ProcessParent();

  template<typename ThreadFunc, typename... Args>
  void start(ThreadFunc threadFunc, Args... args) {

    // initialize shared memory for parent
    shmid_ = shmget(IPC_PRIVATE, sharedMemPageSize_, IPC_CREAT | 0x600 | IPC_EXCL);
    if (shmid_ < 0) {
      printf("unable to create shared mem. shmid: %d, errno: %s\n", shmid_, strerror(errno));
      return;
    }
    void *shm = shmat(shmid_, nullptr, 0);
    if (shm == reinterpret_cast<void *>(-1)) {
      printf("unable to attach shared mem. errno: %s\n", strerror(errno));
      int retval = shmctl(shmid_, IPC_RMID, NULL);
      if (retval < 0) {
        printf("unable to remove shmid\n");
      }
      //close(shmid_);
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
      // attach shared mem
      void *shm = shmat(shmid_, nullptr, 0);
      if (shm == reinterpret_cast<void *>(-1)) {
        printf("unable to attach shared mem in child. errno: %s. exiting child process\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      printf("shared mem child: %p\n", shm);
      ProcessChild processChild(shm, sharedMemPageSize_);

      // exec thread func
      int retval = threadFunc(processChild, args...);

      // detach shared mem
      int retval_dt = shmdt(shm);
      if (retval_dt < 0) {
        printf("unable to detach shared mem in child. error: %d\n", retval_dt);
      }
      exit(retval);
    }
  }

  void stop() {
    if (pid_ < 0) {
      printf("child is already stopped\n");
      return;
    }
    requestStop();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    printf("killing 0x%.8X pid\n", pid_);
    int retval = kill(pid_, SIGKILL);
    printf("kill returned status: %d\n", retval);
    int status = 0;
    pid_t waitpid_retval = waitpid(pid_, &status, 0);
    printf("waitpid_retval: 0x%.8X, status: 0x%.8X\n", waitpid_retval, status);

    // free shared mem resources
    if (sharedMemParent_ == nullptr) {
      printf("shared mem is already freed in parent.\n");
      return;
    }
    retval = shmdt(sharedMemParent_);
    if (retval < 0) {
      printf("unable to detach shared mem in parent. error: %d\n", retval);
    } else if (retval == 0) {
      sharedMemParent_ = nullptr;
    }
    //close(shmid_);
    retval = shmctl(shmid_, IPC_RMID, NULL);
    if (retval < 0) {
      printf("unable to remove shmid\n");
    }
    shmid_ = -1;
  }



private:
  static constexpr size_t sharedMemPageSize_ = 4096;
  void requestStop();


  //ThreadFunc threadFunc_;
  pid_t pid_ = -1;
  void *sharedMemParent_ = nullptr;
  int shmid_ = -1;
};

#endif /* PROCESSPARENT_H_ */
