/*
 * process.cpp
 *
 *  Created on: May 12, 2023
 *      Author: user
 */

#include "process.h"

Process::~Process() {

}

bool Process::isStopRequested() const {
  if (sharedMemChild_ == nullptr) {
    printf("child mem is not initialized\n");
    return false;
  }
  return *static_cast<int *>(sharedMemChild_);
}

void Process::requestStop() {
  if (sharedMemParent_ == nullptr) {
    printf("parent mem is not initialized\n");
    return;
  }
  *static_cast<int *>(sharedMemParent_) = 1;
}
