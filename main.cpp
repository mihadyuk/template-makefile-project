#include <assert.h>
#include <iostream>
#include "stringUtils.h"

using namespace utils;
using namespace std;

static void printDirName(const char *dir) {
  printf("src: %s, dst: %s \n", dir, utils::dirname(dir).c_str());
}

int main(int argc, char *argv[]) {

  cout << "template makefile project \r\n";

  printDirName("/tmp/test-dir/settings.ini");
  printDirName("/settings.ini");
  printDirName("settings.ini");
  printDirName("/");
  printDirName("");
  //printDirName(nullptr);

  return 0;
}


