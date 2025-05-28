#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H
#include <stddef.h>
#include <vector>

class SlidingWindow
{
public:
    SlidingWindow();
    void run();
private:
    std::vector<float> medianSlidingWindow(const std::vector<int>& nums, size_t k);
};

#endif // SLIDINGWINDOW_H
