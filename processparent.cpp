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
