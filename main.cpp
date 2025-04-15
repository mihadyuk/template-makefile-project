#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <stdint.h>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <algorithm>
//#include "qt_subdir/qtexampleskeleton.h"
#include "romantointeger.h"

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

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.




  Example 1:

  Input: digits = "23"
  Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

  Example 2:

  Input: digits = ""
  Output: []

  Example 3:

  Input: digits = "2"
  Output: ["a","b","c"]


   Constraints:

                 0 <= digits.length <= 4
                    digits[i] is a digit in the range ['2', '9'].

*/
std::vector<std::string> letterCombinations(const std::string &digits) {
    std::vector<std::string> retval{""};

    const std::unordered_map<int, std::string> map = {{1, ""},
                                                      {2, "abc"},
                                                      {3, "def"},
                                                      {4, "ghi"},
                                                      {5, "jkl"},
                                                      {6, "mno"},
                                                      {7, "pqrs"},
                                                      {8, "tuv"},
                                                      {9, "wxyz"}};
    //std::vector<std::string> temp0, temp1, temp2;
    std::vector<std::string> temp;
    for (size_t digit_pos = 0; digit_pos < digits.size(); digit_pos++) {
        std::string pad = map.at(std::atoi(std::string(&digits[digit_pos], 1).c_str()));
        if (pad.size() == 0)
            continue;
        for (size_t i = 0; i < retval.size(); i++) {
            for (size_t j = 0; j < pad.size(); j++) {
                temp.push_back(retval[i] + pad[j]);
            }
        }
        retval = std::move(temp);
    }
    return retval;
}

/*
30. Substring with Concatenation of All Words
    Hard
        Topics
            Companies
                You are given a string s and an array of strings words. All the strings of words are of the same length.

    A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

    For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
                                                                                              Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.



                Example 1:

                Input: s = "barfoothefoobarman", words = ["foo","bar"]

               Output: [0,9]

                Explanation:

              The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
              The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.

              Example 2:

              Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]

              Output: []

            Explanation:

                          There is no concatenated substring.

                          Example 3:

                                      Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]

                   Output: [6,9,12]

                            Explanation:

                                          The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"].
                                          The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"].
                                          The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"].



                                          Constraints:

                                                        1 <= s.length <= 104
                   1 <= words.length <= 5000
                   1 <= words[i].length <= 30
                   s and words[i] consist of lowercase English letters.
*/
std::vector<size_t> findSubstring(const std::string &s, const std::vector<std::string> &words) {
    std::vector<size_t> indicies;

    std::vector<std::string> permutated_words(words);
    std::sort(permutated_words.begin(), permutated_words.end());
    std::vector<std::string> substrs;
    do {
        std::string concat;
        for (const std::string &word : permutated_words) {
            concat += word;
        }
        substrs.push_back(concat);

    } while (std::next_permutation(permutated_words.begin(), permutated_words.end()));


    for (const std::string &substr : substrs) {
        std::string::size_type pos = 0;
        pos = s.find(substr, pos);
        while (pos != std::string::npos) {
            indicies.push_back(pos);
            pos = s.find(substr, pos + substr.size());
        }
    }

    return indicies;
}

int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }

    RomanToInt().run();
    //auto vec = twoSum({2, 7, 11, 15}, 9);
    //vec = twoSum({3, 2, 4}, 6);
    auto substr1 = findSubstring("barfoothefoobarman", {"foo","bar"});
    auto substr2 = findSubstring("wordgoodgoodgoodbestword", {"word","good","best","word"});
    auto substr3 = findSubstring("barfoofoobarthefoobarman", {"bar","foo","the"});


    auto vec = letterCombinations("");
    auto vec1 = letterCombinations("1");
    auto vec12 = letterCombinations("12");
    auto vec21 = letterCombinations("21");
    auto vec2 = letterCombinations("2");
    auto vec23 = letterCombinations("23");
    auto vec234 = letterCombinations("234");
    auto vec32 = letterCombinations("32");
    auto vec37 = letterCombinations("37");

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


