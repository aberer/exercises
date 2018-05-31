#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <map>
#include <iostream>

using namespace std;

vector<string> split_string(string);


class Trie
{
public:
    using StrCIter = std::string::const_iterator;

public:
    // _________________________________________________________________________
    Trie(std::string prefix = "");


    // _________________________________________________________________________
    void                                add(StrCIter begin, StrCIter end);

    // _________________________________________________________________________
    void                                add(std::string val)
    { add(val.begin(), val.end()); }

    // _________________________________________________________________________
    std::size_t                         find(const std::string& contact) const
    { return find(contact.begin(), contact.end()); }

    // _________________________________________________________________________
    std::size_t                         find(StrCIter begin, StrCIter end) const;

    // _________________________________________________________________________
    friend std::ostream& operator<<(std::ostream&, const Trie& trie);

private:
    // unordered map has a problem with incomplete types
    using Children =  std::map<char, Trie>;

private:
    void                                insertChild(StrCIter iter, StrCIter end);

private:
    std::string    _prefix;
    Children       _children;
};



std::ostream& operator<<(std::ostream& os, const Trie& trie)
{
    os << trie._prefix;

    if (!trie._children.empty())
    {
        os << '(';

        auto isFirst(true);

        std::for_each(
            trie._children.begin(),
            trie._children.end(),
            [&isFirst,&os](const auto& it)
            {
                os << (isFirst ? "": ",") << '\'' << it.first <<  '\'' << it.second;
                isFirst = false;
            });

        os << ')';
    }

    return os;
}



// _____________________________________________________________________________
Trie::Trie(std::string prefix)
    : _prefix(std::move(prefix))
{}



// _____________________________________________________________________________
void
Trie::insertChild(StrCIter queryBegin, StrCIter queryEnd)
{
    if (queryBegin == queryEnd)
    {
        _children['#'] = Trie();
    }
    else
    {
        // used to be a leaf
        if ((_prefix != "" && _children.empty()))
            _children['#'] = Trie();

        _children[*queryBegin] =
            queryBegin + 1 == queryEnd
            ? Trie("#")
            : Trie(std::string(queryBegin+1, queryEnd));
    }
}


// _____________________________________________________________________________
void
Trie::add(StrCIter begin, StrCIter end)
{
    StrCIter queryIter;
    StrCIter prefixIter;

    std::tie(queryIter, prefixIter) = std::mismatch(
        begin, end, _prefix.begin());

    if (prefixIter == _prefix.end())        // full prefix matched
    {
        if (queryIter != end)       // word not there yet
        {
            auto matchingChild(_children.find(*queryIter));

            if (matchingChild != _children.end())
            {
                matchingChild->second.add(queryIter+1, end);
                return;
            }
        }
    }
    else        // partial match, we are splitting the node
    {
        char remainderChar(*prefixIter);
        std::string remainderString(prefixIter+1, _prefix.cend());
        Trie t(remainderString);
        t._children = std::move(_children);

        _children.clear();
        _prefix = std::string(_prefix.cbegin(), prefixIter);
        _children[remainderChar] = std::move(t);
    }

    insertChild(queryIter, end);
}


// _____________________________________________________________________________
std::size_t
Trie::find(StrCIter queryBegin, StrCIter queryEnd) const
{
    StrCIter queryIter;
    StrCIter prefixIter;

    std::tie(queryIter, prefixIter) = std::mismatch(
        queryBegin, queryEnd, _prefix.begin());

    if (queryIter == queryEnd)
    {
        return _children.empty()
            ? 1u
            : std::accumulate(
                _children.begin(),
                _children.end(),
                0u,
                [&](std::size_t res, const auto& t)
                { return res + t.second.find(queryIter, queryEnd); });
    }
    else
    {
        auto it = _children.find(*queryIter);

        return it == _children.end()
            ? 0u
            : it->second.find(queryIter+1, queryEnd);
    }
}


// _____________________________________________________________________________
#ifndef TEST_CASE
int                               main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Trie trie;

    for (int n_itr = 0; n_itr < n; n_itr++)
    {
        string         opContact_temp;
        getline(cin, opContact_temp);

        vector<string> opContact = split_string(opContact_temp);

        string         op = opContact[0];

        string         contact = opContact[1];

        if (op == "add")
        {
            trie.add(contact.begin(), contact.end());
        }
        else if (op == "find")
        {
            cout << trie.find(contact) << "\n";;
        }
    }

    return 0;
}
#endif


// _____________________________________________________________________________
vector<string>                    split_string(
    string input_string)
{
    string::iterator new_end = unique(
            input_string.begin(),
            input_string.end(),
            [](const char&x, const char&y)
    {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
        input_string.pop_back();

    vector<string>   splits;
    char             delimiter = ' ';

    size_t           i = 0;
    size_t           pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length())
                                         - i + 1));

    return splits;
}
