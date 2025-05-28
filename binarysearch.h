#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <vector>

class BinarySearch
{
public:
    BinarySearch();
    void run();
private:
    int search(const std::vector<int>& nums, int target);
};

#endif // BINARYSEARCH_H
