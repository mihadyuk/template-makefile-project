#ifndef GROUPANAGRAMS_H
#define GROUPANAGRAMS_H
#include <string>
#include <vector>

class GroupAnagrams
{
public:
    void run();
private:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs);
};

#endif // GROUPANAGRAMS_H
