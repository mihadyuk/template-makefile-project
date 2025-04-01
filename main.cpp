#include <assert.h>
#include <iostream>
#include <stdio.h>

#include <unistd.h>


int main(int argc, char *argv[]) {

  //std::cout << "template makefile project \r\n";
  printf("before fork\n");
  pid_t pid = fork();
  if (pid == 0) {
    printf("child proc. proc id 0x%.8X\n", getpid());
  }
  else if (pid > 0) {
    printf("parent proc. child proc id 0x%.8X, parent proc id 0x%.8X\n", pid, getpid());
  }
  else {
    printf("fork() failed. return code %d", pid);
  }
  return 0;
}


