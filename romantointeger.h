#ifndef ROMANTOINTEGER_H
#define ROMANTOINTEGER_H
#include <string>
#include <stdint.h>

class RomanToInt
{
public:
    void run();
private:
    uint16_t romanToInt(const std::string &roman);
};

#endif // ROMANTOINTEGER_H
