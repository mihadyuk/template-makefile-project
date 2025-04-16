#ifndef FINDSUBSTRING_H
#define FINDSUBSTRING_H
#include <vector>
#include <stddef.h>
#include <string>

class FindSubstring
{
public:
    void run();
private:
    std::vector<size_t> findSubstring(const std::string &s, const std::vector<std::string> &words);
};

#endif // FINDSUBSTRING_H
