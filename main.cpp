//#include <assert.h>
//#include <iostream>
//#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <bitset>
#include "unit1.h"
#include "unit2.h"
#include "unit2.h"

/*
 practical guide to bare metal C++
 https://legacy.gitbook.com/book/arobenko/bare_metal_cpp/details

*/

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
    return static_cast<TestEnum>(static_cast<uint32_t>(val1) | static_cast<uint32_t>(val2));
}

typedef void (*FUNC_HANDLER)(void *);

static void func0(void *param) {
    (void)param;
    printf("func0 %p", param);
}

static void func1(void *param) {
    (void)param;
    printf("func1 %p", param + 1);
}

static void func2(void *param) {
    (void)param;
    printf("func2 %p", param + 2);
}

static void func3(void *param) {
    (void)param;
    printf("func3 %p", param + 3);
}

static const FUNC_HANDLER g_funcTable[] =
{
    func0,
    func1,
    func2,
    func3
};

static void funcHandler(uint32_t index, void *param) {
    switch (index) {
        case 11:
            func0(param);
        break;
        case 1:
            func1(param);
        break;
        case 3:
            func2(param);
        break;
        case 7:
            func3(param);
        break;
        default:
        break;
    };
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

  //TestEnum a = TestEnum::Val1 | TestEnum::Val2 | TestEnum::Val3;
  //printf("%lu", (uint32_t)a);
  //for (uint32_t i = 0; i < 2; i++) {
  //    funcHandler(i, (void *)i);
      //g_funcTable[i](nullptr);
  //}
  std::bitset<4> bits;
  bits[2] = 1;
  bits[1] = 1;
  //uint32_t i = 0;
  //scanf("%lu", &i);
  printf("%d %d", sizeof(bits), bits[2]);
  //funcHandler(i, (void *)i);
  //g_funcTable[i]((void *)i);
  return 0;
}
//#pragma GCC pop_options


