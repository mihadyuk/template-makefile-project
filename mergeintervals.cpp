#include <algorithm>
#include "mergeintervals.h"

MergeIntervals::MergeIntervals() {}

/*
56. Merge Intervals
Medium
Topics
premium lock icon
Companies
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.



Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


Constraints:

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
*/
std::vector<MergeIntervals::Interval> MergeIntervals::merge(const std::vector<MergeIntervals::Interval> &intervals) {
    std::vector<Interval> merged, intervals_internal(intervals);

    std::sort(intervals_internal.begin(), intervals_internal.end());

    merged.push_back(intervals_internal[0]);
    for (size_t i = 1; i < intervals_internal.size(); i++) {
        std::vector<int> &prev = merged.back();

        // If overlapping, merge intervals
        if (prev[1] >= intervals_internal[i][0]) {
            prev[1] = std::max(prev[1], intervals_internal[i][1]);
        } else {
            merged.push_back(intervals_internal[i]);
        }
    }

    return merged;
}

void MergeIntervals::run() {
    auto res1 = merge({{1, 3}, {2, 6}, {8, 10}, {15, 18}});
    auto res2= merge({{1, 4}, {4, 5}});
}
