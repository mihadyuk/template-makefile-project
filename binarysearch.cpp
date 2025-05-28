#include <stddef.h>
#include "binarysearch.h"

BinarySearch::BinarySearch() {}

/*
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums.
If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.



Example 1:

Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4
Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1


Constraints:

1 <= nums.length <= 104
-104 < nums[i], target < 104
All the integers in nums are unique.
nums is sorted in ascending order.
*/
int BinarySearch::search(const std::vector<int>& nums, int target) {

    if (nums.size() == 0)
        return -1;
    if (nums.size() == 1) {
        if (nums[0] == target)
            return 0;
        return -1;
    }

    size_t first_pos = 0;
    size_t last_pos = nums.size() - 1;
    while (last_pos >= first_pos) {
        size_t medium_pos = (first_pos + last_pos) / 2;
        if (target > nums[medium_pos]) {
            first_pos = medium_pos + 1;
            continue;
        }
        else if (target < nums[medium_pos]) {
            last_pos = medium_pos - 1;
            continue;
        }
        return (int)medium_pos;
    }
    return -1;
}

void BinarySearch::run() {
    auto res00 = search({-1, 0 , 1}, 1);
    auto res01 = search({-1, 0 , 1}, -1);
    auto res02 = search({-1, 0 , 1}, 0);
    auto res1 = search({-1,0,3,5,9,12}, 9);
    auto res2 = search({-1,0,3,5,9,12}, 2);

    (void)res00;
    (void)res01;
    (void)res02;
    (void)res1;
    (void)res2;
}
