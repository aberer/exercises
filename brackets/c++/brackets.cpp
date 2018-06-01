#include <bits/stdc++.h>

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


using StrCIter = std::string::const_iterator;
using StrRevCIter = std::string::const_reverse_iterator;


// _____________________________________________________________________________
auto isBalancedImpl(
    const std::string&  refString,
    StrCIter            cursor,
    StrRevCIter         lastOpening)
    -> bool
{
    if (cursor == refString.cend()
        && lastOpening == refString.crend())
    {
        return true;
    }
    else if (isOpenBracket(*cursor))
    {
        ++cursor;

        return isBalancedImpl(
            refString, cursor, std::make_reverse_iterator(cursor));
    }
    else
    {
        // closing bracket

        if (lastOpening == refString.crend())
        {
            // no more brackets
            return false;
        }
        else if (!isMatching(*cursor, *lastOpening))
        {
            // brackets do not match
            return false;
        }
        else
        {
            // brackets matched
            return isBalancedImpl(
                refString,
                cursor + 1,
                std::find_if(lastOpening + 1, refString.crend(), isOpenBracket));
        }
    }
}



// _____________________________________________________________________________
auto isBalanced(
    const std::string& expression)
    -> bool
{
    return isBalancedImpl(
        expression, expression.cbegin(), expression.crbegin());
}



// _____________________________________________________________________________
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
