#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <stdint.h>
#include <string>

using Buffer = std::vector<uint8_t>;

std::string buffer_to_str(const Buffer &buffer);

#endif // UTILS_H
