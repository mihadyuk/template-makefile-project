#include <unordered_map>
#include <stdexcept>
#include "romantointeger.h"


/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.



Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.


Constraints:

1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].

*/
uint16_t RomanToInt::romanToInt(const std::string &roman) {
    const std::unordered_map<std::string, uint16_t> romanToIntMap = {{"I", 1},
                                                                    {"V", 5},
                                                                    {"X", 10},
                                                                    {"L", 50},
                                                                    {"C", 100},
                                                                    {"D", 500},
                                                                    {"M", 1000},
                                                                    {"IV", 4},
                                                                    {"IX", 9},
                                                                    {"XL", 40},
                                                                    {"XC", 90},
                                                                    {"CD", 400},
                                                                    {"CM", 900}};
    std::string::size_type pos = 0;
    uint16_t digits = 0;
    while (pos < roman.size()) {
        std::string substr = roman.substr(pos, 2);
        auto it = romanToIntMap.find(substr);
        if (it != romanToIntMap.cend()) {
            digits += it->second;
            pos += 2;
        }
        else {
            substr = roman.substr(pos, 1);
            it = romanToIntMap.find(substr);
            if (it == romanToIntMap.cend())
                throw std::out_of_range("unregognized roman number " + substr);
            digits += it->second;
            pos += 1;
        }
    }

    return digits;
}

void RomanToInt::run() {
    [[maybe_unused]] auto num3 = romanToInt("III");
    [[maybe_unused]] auto num58 = romanToInt("LVIII");
    [[maybe_unused]] auto num1994 = romanToInt("MCMXCIV");
    [[maybe_unused]] auto num4 = romanToInt("IV");
    [[maybe_unused]] auto num1 = romanToInt("I");


    //(void)num3;
    //(void)num58;
    //(void)num1994;
}


