#include <stack>
#include "validparentheses.h"

ValidParentheses::ValidParentheses() {}

/*
20. Valid Parentheses
Easy
Topics
premium lock icon
Companies
Hint
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.


Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true



Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
*/
bool ValidParentheses::isValid(const std::string &s) {
    std::stack<char> stack;

    for (const auto &ch : s) {
        if (stack.size() == 0) {
            if (ch == '(' || ch == '[' || ch == '{')
                stack.push(ch);
            else
                return false;
        }
        else {
            if (stack.top() == '(' && ch == ')')
                stack.pop();
            else if (stack.top() == '[' && ch == ']')
                stack.pop();
            else if (stack.top() == '{' && ch == '}')
                stack.pop();
            else if (ch == '(' || ch == '[' || ch == '{')
                stack.push(ch);
            else
                return false;
        }
    }
    return true;
}


void ValidParentheses::run() {
    auto res0 = isValid("()");
    auto res1 = isValid("()[]{}");
    auto res2 = isValid("(]");
    auto res3 = isValid("([])");
    auto res4 = isValid("([{}])");
    auto res5 = isValid("([{([])}])");

    (void)res0;
    (void)res1;
    (void)res2;
    (void)res3;
    (void)res4;
    (void)res5;
}

