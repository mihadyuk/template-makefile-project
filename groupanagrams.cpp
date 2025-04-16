#include <unordered_map>
#include <stdint.h>
#include "groupanagrams.h"

/*
49. Group Anagrams
Medium
Topics
Companies
Given an array of strings strs, group the anagrams together. You can return the answer in any order.



Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]

Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:

There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
Example 2:

Input: strs = [""]

Output: [[""]]

Example 3:

Input: strs = ["a"]

Output: [["a"]]



Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.

*/
std::vector<std::vector<std::string>> GroupAnagrams::groupAnagrams(const std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> retval;
    std::unordered_map<uint32_t, std::vector<std::string>> map;

    for (const auto &str : strs) {
        uint32_t sum = 0;
        for (const char &ch : str) {
            sum += static_cast<uint32_t>(ch);
        }
        map[sum].push_back(str);
    }

    for (const auto &it : map) {
        retval.push_back(it.second);
    }
    return retval;
}

void GroupAnagrams::run() {
    auto retval1 = groupAnagrams({"eat","tea","tan","ate","nat","bat"});
    auto retval2 = groupAnagrams({"a"});
    auto retval3 = groupAnagrams({""});
}
