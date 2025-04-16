#include <iostream>
#include "reverseint.h"

//reverse int, example 321 -> 123


Buffer ReverseInt::int_to_bcd(int16_t val) {
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


int16_t ReverseInt::reverse(int16_t val) {

    Buffer bcd = int_to_bcd(val);
    int16_t scale = 1;
    int16_t retval = 0;
    for (const auto &digit : bcd) {
        retval += scale * digit;
        scale *= 10;
    }
    return val >= 0 ? retval : -retval;
}

void ReverseInt::run() {
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
}
