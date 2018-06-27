#include <assert.h>
#include <iostream>
#include <stdint.h>
#include "exceptions/exceptionsMain.h"
#include <new>

class Test {
    int32_t m_val = 0;
public:
    Test(int32_t val) : m_val(val) {
        std::cout << "Test: ctor " << m_val << std::endl;
    }
    Test(const Test &src) {
        std::cout << "Test: copy ctor " << m_val << std::endl;
    }
    Test(const Test &&src) {
            std::cout << "Test: move ctor " << m_val << std::endl;
    }
    ~Test() {
        std::cout << "Test: dtor " << std::endl;
    }
    Test& operator=(const Test& src) {
        if (this == &src)
            return *this;
        std::cout << "Test: operator= " << std::endl;
        return *this;
    }
};

int main(int argc, char *argv[]) {

  //Test *buffer = (Test *)malloc(sizeof(Test));
  uint8_t *buffer = (uint8_t *)malloc(sizeof(Test));

  //*buffer = Test(10);
  *(Test *)buffer = Test(10);
  //new (buffer) Test(10);
  ((Test *)buffer)->~Test();

  free(buffer);

  //std::cout << "template makefile project \r\n";
  //exceptionsMain();
  return 0;
}


