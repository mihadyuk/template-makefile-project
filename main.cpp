#include <assert.h>
#include <iostream>
#include <chrono>

#include "ppp.h"



int main(int argc, char *argv[]) {
#if 0
  execl("/usr/bin/pppd", "/dev/ttyUSB0", "115200", "nodetach", "192.168.100.10:192.168.100.20", "nocrtscts", "noauth",
              "local", "persist", "unit", "3", "lcp-echo-failure", "3", "lcp-echo-interval", "20",
              "lcp-max-configure","9999", nullptr);

  return 0;
#endif
  PPP ppp1;
  ppp1.start();

  int inval;
  scanf("%d", &inval);
  //std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  ppp1.stop();

  std::cout << "template makefile project \r\n";
  return 0;
}


