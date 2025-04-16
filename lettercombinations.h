#ifndef LETTERCOMBINATIONS_H
#define LETTERCOMBINATIONS_H
#include <vector>
#include <string>

class LetterCombinations
{
public:
    void run();
private:
    std::vector<std::string> letterCombinations(const std::string &digits);
};

#endif // LETTERCOMBINATIONS_H
