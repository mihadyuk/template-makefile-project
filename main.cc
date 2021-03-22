#include <assert.h>
#include <iostream>
#include "settings.h"

using namespace verifone::service::usbcomm;

int main(int argc, char *argv[]) {

  std::cout << "template makefile project \r\n";

  Settings &settings = Settings::instance();
  settings.open("test.xml");
  return 0;
}


