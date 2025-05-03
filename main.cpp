#include <assert.h>
#include <iostream>
#include <stdint.h>

#include <condition_variable>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

#include "exceptionsMain.h"
#include "memallocMain.h"
#include "classesMain.h"
#include "aggregateInitMain.h"
#include "templatesMain.h"
#include "round.h"
#include "crossRefMain.h"
#include "smartPtrsMain.h"
#include "threadsMain.h"
#include "VirtualInheritanceMain.h"
#include "subscriberMain.h"


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

static std::atomic<bool> g_shouldClose(false);
static std::mutex g_mutex_2;
static void thread_func_2(void *p)
{
    while (1)
    {
        printf("wait for unlock\n");
        g_mutex_2.lock();
        printf("unlocked in thread\n");
        if (g_shouldClose)
        {
            break;
        }
    }
    printf("thread closed\n");
}

#define DIALOG_NAME__(num) Dialog##num
#define DIALOG_NAME_(num) DIALOG_NAME__(num)

#define DIALOG_NUM_2 2
#define DIALOG_NUM 1

#define DIALOG_NAME DIALOG_NAME_(DIALOG_NUM)

#define STR_(x) #x
#define STR(x) STR_(x)
#define DIALOG_NAME_STR STR(DIALOG_NAME)

int main(int argc, char *argv[]) {

  std::cout << DIALOG_NAME_STR
            << " " STR(DIALOG_NAME)
            << " " STR_(DIALOG_NAME)
            << " "
            << STR(DIALOG_NAME_(DIALOG_NUM_2))
            << std::endl;

  //std::cout << "template makefile project \r\n";
  //exceptionsMain();
  //memallocMain();
  //classesMain();
  //aggregateInitMain();
  templatesMain();
  //threadsMain();
  //subscriberMain();
  return 0;
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
  g_mutex_2.lock();
  std::thread thread_2(thread_func_2, nullptr);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  g_mutex_2.unlock();
  g_mutex_2.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  g_mutex_2.unlock();
  g_shouldClose = true;
  g_mutex_2.unlock();
  thread_2.join();

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


