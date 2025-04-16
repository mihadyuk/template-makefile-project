#include "utils.h"

std::string buffer_to_str(const Buffer &buffer) {
    std::string str;
    for (const auto &item : buffer) {
        str += std::to_string(item) + " ";
    }
    return str;
}
