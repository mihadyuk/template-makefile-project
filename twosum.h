#ifndef TWOSUM_H
#define TWOSUM_H
#include <vector>

class TwoSum
{
public:
    void run();
private:
    std::vector<int> twoSum(const std::vector<int> &data, int target);
};

#endif // TWOSUM_H
