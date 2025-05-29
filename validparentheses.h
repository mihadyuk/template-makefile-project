#ifndef VALIDPARENTHESES_H
#define VALIDPARENTHESES_H
#include <string>

class ValidParentheses
{
public:
    ValidParentheses();
    void run();
private:
    bool isValid(const std::string &s);
};

#endif // VALIDPARENTHESES_H
