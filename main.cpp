#include <assert.h>
#include <iostream>
#include <stdio.h>

int f(int *a) {
    int b;

    if (!a)
       f(&b);
    return (&b > a);
}

int main(int argc, char *argv[]) {

  printf(f(0)? "true \n" : "false \n");

  //std::cout << "\n template makefile project \n";
  return 0;
}


