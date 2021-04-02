#include <assert.h>
#include <iostream>
#include <stdint.h>
#include "exceptions/exceptionsMain.h"
#include "mem_alloc/memallocMain.h"
#include "classes/classesMain.h"
#include "aggregateInit/aggregateInitMain.h"
#include "templatesMain.h"
#include "round.h"
#include "crossRefMain.h"
#include "smartPtrsMain.h"
#include "VirtualInheritanceMain.h"

#include <condition_variable>
#include <chrono>
#include <future>

static int thread_func(void *p)
{
    return 1;
}



int main(int argc, char *argv[]) {

  //std::cout << "template makefile project \r\n";
  //exceptionsMain();
  //memallocMain();
  //classesMain();
  //aggregateInitMain();
  //templatesMain();
  //std::cout << roundToNearestPow2<uint32_t>(48);
  //crossRefMain();
  //smartPtrsMain();
  //virtualInheritanceMain();
  //std::condition_variable cv;
  //std::mutex mutex;
  //std::unique_lock<std::mutex> lk(mutex);
  //cv.notify_all();
  //std::cv_status status = cv.wait_for(lk, std::chrono::milliseconds(0));
  //assert(status == std::cv_status::no_timeout);
  //std::future<int> result = std::async(std::launch::async, thread_func, nullptr);
  //auto result = std::async(std::launch::async, thread_func, nullptr);
  return 0;
}


