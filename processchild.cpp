/*
 * processchild.cpp
 *
 *  Created on: May 16, 2023
 *      Author: user
 */

#include "processchild.h"

ProcessChild::ProcessChild(void *sharedMem, size_t sharedMemSize) :
  sharedMem_(sharedMem),
  sharedMemSize_(sharedMemSize)
{
}

ProcessChild::~ProcessChild() {
  // TODO Auto-generated destructor stub
}

bool ProcessChild::isStopRequested() const {
  if (sharedMem_ == nullptr) {
    printf("child mem is not initialized\n");
    return false;
  }
  return *static_cast<int *>(sharedMem_);
}


