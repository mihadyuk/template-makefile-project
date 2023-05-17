/*
 * process.cpp
 *
 *  Created on: May 12, 2023
 *      Author: user
 */

#include "processparent.h"

ProcessParent::~ProcessParent() {

}

void ProcessParent::requestStop() {
  if (sharedMemParent_ == nullptr) {
    printf("parent mem is not initialized\n");
    return;
  }
  *static_cast<int *>(sharedMemParent_) = 1;
}

int ProcessParent::sharedMemInit(size_t pageSize) {
  int retval = shmget(IPC_PRIVATE, pageSize, IPC_CREAT | 0x600 | IPC_EXCL);
  if (retval < 0) {
    printf("unable to create shared mem. shmid: %d, errno: %s\n", retval, strerror(errno));
  }
  return retval;
}

void ProcessParent::sharedMemDeinit(int shmid) {
  int retval = shmctl(shmid, IPC_RMID, NULL);
  if (retval < 0) {
    printf("unable to remove shmid\n");
  }
}

void *ProcessParent::sharedMemAttach(int shmid) {
  void *shm = shmat(shmid, nullptr, 0);
  if (shm == reinterpret_cast<void *>(-1)) {
    printf("unable to attach shared mem. errno: %s\n", strerror(errno));
  }
  return shm;
}

void ProcessParent::sharedMemDetach(void *sharedMem) {
  int retval = shmdt(sharedMem);
  if (retval < 0) {
    printf("unable to detach shared mem in child. error: %d\n", retval);
  }
}

bool ProcessParent::isSharedMemValid(const void *sharedMem) {
  return sharedMem != reinterpret_cast<void *>(-1);
}
