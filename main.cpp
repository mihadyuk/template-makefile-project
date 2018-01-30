#include <assert.h>
#include <iostream>
#include <sys/resource.h>

static uint32_t i;

/*
 * http://man7.org/linux/man-pages/man2/getrlimit.2.html
 * https://stackoverflow.com/questions/2275550/change-stack-size-for-a-c-application-in-linux-during-compilation-with-gnu-com
 * */
void recursive()
{
  i++;
  if ( i % 10000U == 0)
    std::cout << i << std::endl;
  recursive();
}

int main(int argc, char *argv[]) {

  /* get stack limit*/
  rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result >= 0) {
    std::cout << "stack: " << rl.rlim_cur << std::endl;
  }
#if 1
  rl.rlim_cur *= 2;

  setrlimit(RLIMIT_STACK, &rl);
#endif

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result >= 0) {
    std::cout << "stack: " << rl.rlim_cur << std::endl;
  }
  //std::cout << "template makefile project \r\n";
  recursive();
  return 0;
}


