//#include <assert.h>
//#include <iostream>
//#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include "unit1.h"
#include "unit2.h"
#include "unit2.h"


struct Test {
  int32_t _a;
  int64_t _b;
  int16_t _c;
};


Test test;
//Test test2 = {4};
int32_t a;
//#pragma GCC push_options
//#pragma GCC optimize ("O2")
volatile char buf[100];
int main(void) {
  g_int32 = 9;	

  //printf("test: %s \r\n", test_extern);
  //std::cout << "template makefile project \r\n";
  a = test._a + unit_get()->m_int32;
  //printf("%ld", a);
  printf("text");
  snprintf((char *)buf, sizeof(buf), "%ld", a);
  return 0;
}
//#pragma GCC pop_options


