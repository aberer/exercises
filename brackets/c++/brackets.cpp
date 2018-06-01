#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

// _____________________________________________________________________________
auto isOpenBracket(char c)
    -> bool
{
    switch (c)
    {
    case '(':
    case '[':
    case '{':
        return true;
    default:
        return false;
    }

}
// _____________________________________________________________________________
auto isMatching(char c, char d)
    -> bool
{
    if (isOpenBracket(c))
        return isMatching(d, c);

    switch (c)
    {
    case ')':
        return d == '(';
    case ']':
        return d == '[';
    case '}':
        return d == '{';
    default:
        return false;
    }
}


// _____________________________________________________________________________
auto isBalanced(const std::string& expression)
    -> bool
{
    std::stack<char> openBrackets;

    auto mismatch(
        std::find_if(
            expression.cbegin(),
            expression.cend(),
            [&openBrackets](char c)
            {
                if (isOpenBracket(c))
                {
                    openBrackets.push(c);
                    return false;
                }
                else if(!openBrackets.empty()
                        && isMatching(c, openBrackets.top()))
                {
                    openBrackets.pop();
                    return false;
                }
                else
                {
                    return true;
                }
            }));

    return mismatch == expression.end() && openBrackets.empty();
}




#ifndef TEST_CASE
int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string expression;
        getline(cin, expression);

        cout << (isBalanced(expression) ? "YES" : "NO") << "\n";
    }

    return 0;
}
#endif
