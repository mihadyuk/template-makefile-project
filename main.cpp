#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include "qt_subdir/qtexampleskeleton.h"

int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }
    QtExampleSkeleton ex;
    std::bitset<8> bits(0x5);
    bits[5] = 1;
    auto str = bits.to_string();
    printf("size %llu, bits : %s\r\n", sizeof(bits), str.c_str());
    return 0;
}


