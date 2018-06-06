//#include <assert.h>
//#include <iostream>
//#include <stdio.h>
#include <stdint.h>
#include "unit1.h"


struct Test {
  int32_t _a;
  int64_t _b;
  int16_t _c;
};


Test test;
//Test test2 = {4};

#pragma GCC push_options
#pragma GCC optimize ("O0")
int main(void) {

  //printf("test: %s \r\n", test_extern);
  //std::cout << "template makefile project \r\n";
  test._a = test._a + unit_get()->m_int32;
  return 0;
}
#pragma GCC pop_options


