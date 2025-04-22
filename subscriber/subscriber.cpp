#include <stdio.h>
#include "subscriber.h"

void Subscriber::notify(const std::string &msg) {
    printf("msg: %s\r\n", msg.c_str());
}


