#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <stdint.h>
#include <vector>
#include <unordered_map>
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

/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

    You may assume that each input would have exactly one solution, and you may not use the same element twice.

        You can return the answer in any order.



        Example 1:

                    Input: nums = [2,7,11,15], target = 9
                 Output: [0,1]
                          Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
    Example 2:

                Input: nums = [3,2,4], target = 6
    Output: [1,2]
             Example 3:

                         Input: nums = [3,3], target = 6
             Output: [0,1]


                      Constraints:

                                    2 <= nums.length <= 104
                                           -109 <= nums[i] <= 109
                                           -109 <= target <= 109
                                       Only one valid answer exists.
*/
std::vector<int> twoSum(const std::vector<int> &data, int target) {
    std::unordered_map<int, int> map;

    for (int i = 0; i < static_cast<int>(data.size()); i++) {
        int sup = target - data[i];
        if (map.contains(data[i]) == false) {
            map[sup] = i;
        }
        else {
            return {i, map[data[i]]};
        }
    }
    return std::vector<int>();
}

int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }

    auto vec = twoSum({2, 7, 11, 15}, 9);
    vec = twoSum({3, 2, 4}, 6);

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


