#include <iostream>
#include <list>
#include <string>

std::list<char> li;
int count = 0;

bool TryToRemove(char ch)
{
    bool removed = false;
    for (auto it = li.begin(); it != li.end();)
    {
        if (*it == ch && ((it != li.begin() && ch - 1 == *std::prev(it)) || (std::next(it) != li.end() && ch - 1 == *std::next(it))))
        {
            it = li.erase(it);
            ++count;
            removed = true;
        }
        else ++it;
    }

    return removed;
}

int main()
{
    int n;
    std::string str;
    std::cin >> n >> str;

    for (char ch : str)
        li.push_back(ch);

    for (char ch = 'z'; ch >= 'b'; --ch)
        while (TryToRemove(ch));

    printf("%d", count);

    return 0;
}