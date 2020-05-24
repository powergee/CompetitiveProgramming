#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <string>
#include <list>

std::vector<std::vector<int>> answer;
std::list<std::pair<char, int>> strList;
std::vector<std::list<std::pair<char, int>>::iterator> removed;

std::string str;

void FindSimple()
{
    std::vector<int> open;
    std::vector<int> close;

    open.push_back(strList.front().first == '(' ? 1 : 0);
    for (auto it = std::next(strList.begin()); it != strList.end(); ++it)
    {
        int last = open.back();
        open.push_back(last + (it->first == '(' ? 1 : 0));
    }

    close.push_back(strList.back().first == ')' ? 1 : 0);
    for (auto it = std::next(strList.rbegin()); it != strList.rend(); ++it)
    {
        int last = close.back();
        close.push_back(last + (it->first == ')' ? 1 : 0));
    }

    int max = -1, maxPos;
    for (int i = 0; i < (int)open.size() - 1; ++i)
    {
        if (std::min(open[i], close[open.size() - 2 - i]) > max)
        {
            max = std::min(open[i], close[open.size() - 2 - i]);
            maxPos = i;
        }
    }

    int i = 0, openCount = 0, closeCount = 0;
    for (auto it = strList.begin(); it != strList.end(); ++i, ++it)
    {
        if (i <= maxPos)
        {
            if (it->first == '(' && openCount < max)
            {
                removed.push_back(it);
                ++openCount;
            }
        }
    }

    i = strList.size() - 1;
    for (auto it = std::prev(strList.end()); it != strList.begin(); --i, it = std::prev(it))
    {
        if (i > maxPos)
        {
            if (it->first == ')' && closeCount < max)
            {
                removed.push_back(it);
                ++closeCount;
            }
        }
    }
}

int main()
{
    std::cin >> str;

    for (int i = 0; i < (int)str.size(); ++i)
        strList.push_back({str[i], i + 1});

    while (true)
    {
        FindSimple();

        if (removed.size() == 0)
            break;

        answer.emplace_back();
        for (auto it : removed)
        {
            answer.back().push_back(it->second);
            strList.erase(it);
        }
        std::sort(answer.back().begin(), answer.back().end());

        int i = 1;
        for (auto it = strList.begin(); it != strList.end(); ++it)
            it->second = i++;

        removed.clear();
    }

    printf("%d\n", (int)answer.size());
    for (auto vec : answer)
    {
        printf("%d\n", (int)vec.size());
        for (int pos : vec)
            printf("%d ", pos);
        printf("\n");
    }

    return 0;
}