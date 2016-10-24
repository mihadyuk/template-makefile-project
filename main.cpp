#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

int f(int *a) {
    int b;

    if (!a)
       f(&b);
    return (&b > a);
}

static uint8_t test_large_array[1024 * 1024 * 128L] = {1, 2, 3, 4};

int main(int argc, char *argv[]) {

  for (uint32_t i = 0; i < sizeof(test_large_array) / sizeof(test_large_array[0]); i++) {
      //test_large_array[i] = 0;
      printf("%d", test_large_array[i]);
  }
  //printf(f(0)? "true \n" : "false \n");

  //std::cout << "\n template makefile project \n";
  return 0;
}


