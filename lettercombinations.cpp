#include <unordered_map>
#include "lettercombinations.h"

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
std::vector<std::string> LetterCombinations::letterCombinations(const std::string &digits) {
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

void LetterCombinations::run() {
    auto vec = letterCombinations("");
    auto vec1 = letterCombinations("1");
    auto vec12 = letterCombinations("12");
    auto vec21 = letterCombinations("21");
    auto vec2 = letterCombinations("2");
    auto vec23 = letterCombinations("23");
    auto vec234 = letterCombinations("234");
    auto vec32 = letterCombinations("32");
    auto vec37 = letterCombinations("37");
}

