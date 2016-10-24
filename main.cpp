#include <assert.h>
#include <iostream>
#include <stdio.h>

int f(int *a) {
    int b;

    if (!a)
       f(&b);
    return (&b > a);
}

static uint8_t test_large_array[1024 * 1024 * 128L];

int main(int argc, char *argv[]) {

  for (uint64_t i = 0; i < sizeof(test_large_array) / sizeof(test_large_array[0]); i++) {
      test_large_array[i] = 0;
      printf("%d", test_large_array[i]);
  }
  //printf(f(0)? "true \n" : "false \n");

  //std::cout << "\n template makefile project \n";
  return 0;
}


