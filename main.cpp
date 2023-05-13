#include <assert.h>
#include <iostream>
#include <chrono>

#include "ppp.h"
#include "process.h"

typedef int (*FUNC_PTR)(int val);
int threadFunc(const Process &process, int val) {
  while (process.isStopRequested() == false) {
    printf("threadFunc val: %d\n", val);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  printf("exiting thread func with value %d\n", val);
  return val;
}


int main(int argc, char *argv[]) {
#if 0
  execl("/usr/bin/pppd", "/dev/ttyUSB0", "115200", "nodetach", "192.168.100.10:192.168.100.20", "nocrtscts", "noauth",
              "local", "persist", "unit", "3", "lcp-echo-failure", "3", "lcp-echo-interval", "20",
              "lcp-max-configure","9999", nullptr);

  return 0;
#endif
  Process process;
  process.start(&threadFunc, 1);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  process.stop();

  process.start(&threadFunc, 0);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  process.stop();

  return 0;
  PPP ppp1;
  ppp1.start();

  int inval;
  scanf("%d", &inval);
  //std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  ppp1.stop();

  std::cout << "template makefile project \r\n";
  return 0;
}


