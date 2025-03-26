/*
 * threadsMain.cpp
 *
 *  Created on: Mar 26, 2025
 *      Author: user
 */
#include <assert.h>
#include "threadsMain.h"
#include "joinableThread.h"



void threadsMain() {

  JoinableThread thread;
  assert(thread.isActive() == false);
  thread.start();
  assert(thread.isActive() == true);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  thread.stop();
  assert(thread.isActive() == false);

  thread.start();
  assert(thread.isActive() == true);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}




