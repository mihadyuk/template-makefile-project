#ifndef REVERSEINT_H
#define REVERSEINT_H
#include "utils.h"

class ReverseInt
{
public:
    void run();
private:
    Buffer int_to_bcd(int16_t val);
    int16_t reverse(int16_t val);
};

#endif // REVERSEINT_H
