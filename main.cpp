#include <assert.h>
#include <iostream>
#include <stdio.h>

extern const char *test_extern;

int main(int argc, char *argv[]) {

  printf("test: %s \r\n", test_extern);
  //std::cout << "template makefile project \r\n";
  return 0;
}


