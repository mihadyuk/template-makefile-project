/*
 * processchild.h
 *
 *  Created on: May 16, 2023
 *      Author: user
 */

#ifndef PROCESSCHILD_H_
#define PROCESSCHILD_H_
#include <stdio.h>

class ProcessChild {
public:
  virtual ~ProcessChild();

  bool isStopRequested() const;
private:
  ProcessChild(void *sharedMem, size_t sharedMemSize);

  void *sharedMem_      = nullptr;
  size_t sharedMemSize_ = 0;

  friend class ProcessParent;
};

#endif /* PROCESSCHILD_H_ */
