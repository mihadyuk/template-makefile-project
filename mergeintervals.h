#ifndef MERGEINTERVALS_H
#define MERGEINTERVALS_H
#include <vector>

class MergeIntervals
{
public:
    using Interval = std::vector<int>;
    MergeIntervals();
    void run();
private:
    std::vector<Interval> merge(const std::vector<Interval> &intervals);
};

#endif // MERGEINTERVALS_H
