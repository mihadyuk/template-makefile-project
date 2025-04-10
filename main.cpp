#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <stdint.h>
#include <vector>
//#include "qt_subdir/qtexampleskeleton.h"

//reverse int, example 321 -> 123
using Buffer = std::vector<uint8_t>;

std::string buffer_to_str(const Buffer &buffer) {
    std::string str;
    for (const auto &item : buffer) {
        str += std::to_string(item) + " ";
    }
    return str;
}

Buffer int_to_bcd(int16_t val) {
    Buffer bcd;

    int16_t scale = 10000;
    uint8_t digit = 0;
    val = (val < 0) ? -val : val;
    bool skip_first_zeroes = true;
    while (scale > 1) {
        digit = val / scale;
        val = val % scale;
        scale /= 10;
        if (skip_first_zeroes && digit)
            skip_first_zeroes = false;

        if (skip_first_zeroes == false)
            bcd.push_back(digit);
    }
    bcd.push_back(val);

    return bcd;
}


int16_t reverse(int16_t val) {

    Buffer bcd = int_to_bcd(val);
    int16_t scale = 1;
    int16_t retval = 0;
    for (const auto &digit : bcd) {
        retval += scale * digit;
        scale *= 10;
    }
    return val >= 0 ? retval : -retval;
}

int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }
    std::bitset<8> bits(0x5);
    bits[5] = 1;
    auto str = bits.to_string();
    printf("size %llu, bits : %s\r\n", sizeof(bits), str.c_str());

    int16_t val = 0;
    std::cout << "val: " << val << ", " << reverse(val) << std::endl;

    val = 12;
    std::cout << "val: " << val << ", " << reverse(val) << std::endl;

    val = 123;
    std::cout << "val: " << val << ", " << reverse(val) << std::endl;

    val = 1234;
    std::cout << "val: " << val << ", " << reverse(val) << std::endl;

    val = -1234;
    std::cout << "val: " << val << ", " << reverse(val) << std::endl;

    return 0;
}


