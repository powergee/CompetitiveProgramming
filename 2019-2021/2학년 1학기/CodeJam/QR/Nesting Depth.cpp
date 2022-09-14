#include <iostream>
#include <list>
#include <string>
#include <algorithm>

typedef std::list<char> List;
typedef List::iterator Iter;

void AddLeft(Iter& it, List& li, int count, char par)
{
    while (count--)
        li.insert(it, par);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int c = 1; c <= T; ++c)
    {
        std::string input;
        List result;
        std::cin >> input;

        for (unsigned i = 0; i < input.size(); ++i)
            result.push_back(input[i]);

        result.push_front('0');
        result.push_back('0');

        for (Iter it = result.begin(); std::next(it) != result.end();)
        {
            int left = *it - '0';
            int right = *(++it) - '0';

            if (left < right)
                AddLeft(it, result, right - left, '(');
            else if (left > right)
                AddLeft(it, result, left - right, ')');
        }

        result.pop_front();
        result.pop_back();
        std::cout << "Case #" << c << ": ";
        for (auto it : result)
            std::cout << it;
        std::cout << '\n';
    }

    return 0;
}