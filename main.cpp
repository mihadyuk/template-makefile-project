#include <assert.h>
#include <iostream>
#include <stdint.h>
#include "exceptions/exceptionsMain.h"
#include "mem_alloc/memallocMain.h"
#include "classes/classesMain.h"
#include "aggregateInit/aggregateInitMain.h"
#include "templatesMain.h"
#include "round.h"

int main(int argc, char *argv[]) {

  //std::cout << "template makefile project \r\n";
  //exceptionsMain();
  //memallocMain();
  //classesMain();
  //aggregateInitMain();
  //templatesMain();
  std::cout << roundToNearestPow2<uint32_t>(1023);
  return 0;
}


