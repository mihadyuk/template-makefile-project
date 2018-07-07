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

enum class TestEnum : uint32_t {
    Default = 0x00,
    Val1    = 0x01,
    Val2    = 0x02,
    Val3    = 0x04,
    Val4    = 0x08
};

constexpr TestEnum operator|(const TestEnum &val1, const TestEnum &val2) {
    return (TestEnum)((uint32_t)val1 | (uint32_t)val2);
}


//Test test;
//Test test2 = {4};
//int32_t a;
//#pragma GCC push_options
//#pragma GCC optimize ("O2")
//volatile char buf[100];
int main(void) {
  //g_int32 = 9;

  //printf("test: %s \r\n", test_extern);
  //std::cout << "template makefile project \r\n";
  //a = test._a + unit_get()->m_int32;
  //printf("%ld", a);
  //printf("text");
  //snprintf((char *)buf, sizeof(buf), "%ld", a);

  TestEnum a = TestEnum::Val1 | TestEnum::Val2 | TestEnum::Val3;
  printf("%lu", (uint32_t)a);
  return 0;
}
//#pragma GCC pop_options


