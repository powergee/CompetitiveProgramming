#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int n, m, q;
std::vector<int> novel;
std::vector<std::pair<int, int>> firstAppeared, lastAppeared;

int countUsing(int first)
{
    int pivot = firstAppeared[first].first;
    auto found = std::lower_bound(lastAppeared.begin(), lastAppeared.end(), std::make_pair(pivot, -1));
    if (found != lastAppeared.end())
        found = std::next(found);
        
    return lastAppeared.end() - found;
}

int countAvailable(int first)
{
    return m - countUsing(first);
}

int main()
{
    scanf("%d %d %d", &n, &m, &q);
    firstAppeared.resize(m+1);
    lastAppeared.resize(m+1);

    firstAppeared[0] = {-1, -1};
    lastAppeared[0] = {-1, -1};

    for (int i = 1; i <= m; ++i)
    {
        firstAppeared[i] = {-1, i};
        lastAppeared[i] = {-1, i};
    }

    for (int i = 0; i < n; ++i)
    {
        int ch;
        scanf("%d", &ch);
        novel.push_back(ch);
    }

    for (int i = 0; i < n; ++i)
        if (firstAppeared[novel[i]].first == -1)
            firstAppeared[novel[i]].first = i;
    
    for (int i = n-1; i >= 0; --i)
        if (lastAppeared[novel[i]].first == -1)
            lastAppeared[novel[i]].first = i;
        
    std::sort(lastAppeared.begin(), lastAppeared.end());

    std::vector<std::pair<Long, int>> queries;
    for (int i = 0; i < q; ++i)
    {
        Long pos;
        scanf("%lld", &pos);
        queries.emplace_back(pos, i);
    }
    std::sort(queries.begin(), queries.end());

    std::vector<std::pair<int, int>> answers(q);
    Long availSum = 0;
    int currRow = 1;
    for (auto query : queries)
    {
        int availInRow;
        while (true)
        {
            availInRow = countAvailable(currRow);
            if (availInRow + availSum < query.first)
            {
                availSum += availInRow;
                ++currRow;
            }
            else break;
        }
        
        
    }

    for (std::pair<int, int> answer : answers)
        printf("%d %d\n", answer.first, answer.second);

    return 0;
}