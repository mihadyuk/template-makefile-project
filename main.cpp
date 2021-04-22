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
#include <mutex>
#include <condition_variable>

static std::mutex g_mutex;
static std::condition_variable g_cv;
static std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> g_timestamp;

static int thread_func(void *p)
{
    std::unique_lock lk(g_mutex);
    //for (int i = 0; i < 3; i++)
    //{
        std::cv_status status = g_cv.wait_for(lk, std::chrono::milliseconds(9223372036854775807ULL/0x1000000));
        printf("cv_status %s, %u\n", (status == std::cv_status::no_timeout)? "no_timeout" : "timeout",
                (uint32_t)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - g_timestamp)).count());
    //}
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
  printf("max timeout %llu\n", std::chrono::milliseconds::max().count());
  g_timestamp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
  printf("start thread %u\n", (uint32_t)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - g_timestamp)).count());
  //g_mutex.lock();
  std::thread thread(thread_func, nullptr);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  //g_mutex.unlock();
  printf("notification %u\n", (uint32_t)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - g_timestamp)).count());
  g_cv.notify_one();
  thread.join();
  return 0;
}


