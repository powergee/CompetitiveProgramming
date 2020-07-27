#include <iostream>
#include <algorithm>
#include <vector>

int n, m, q;
std::vector<int> novel;
std::vector<std::pair<int, int>> firstAppeared, lastAppeared;

int countAvailable(int first, int right)
{
    int pivot = firstAppeared[first].first;
    auto found = std::lower_bound(lastAppeared.begin(), lastAppeared.end(), std::make_pair(pivot, -1));
    if (found != lastAppeared.end())
        found = std::next(found);
    
    int count = lastAppeared.end() - found;
    return std::max(0, count);
}

int countAvailable(int first, int left, int right)
{
    return countAvailable(first, right) - countAvailable(first, left-1);
}



int main()
{
    scanf("%d %d %d", &n, &m, &q);
    firstAppeared.resize(m);
    lastAppeared.resize(m);

    for (int i = 0; i < m; ++i)
    {
        firstAppeared[i] = {-1, i};
        lastAppeared[i] = {-1, i};
    }

    for (int i = 0; i < n; ++i)
    {
        int ch;
        scanf("%d", &ch);
        novel.push_back(ch-1);
    }

    for (int i = 0; i < n; ++i)
        if (firstAppeared[novel[i]].first == -1)
            firstAppeared[novel[i]].first = i;
    
    for (int i = n-1; i >= 0; --i)
        if (lastAppeared[novel[i]].first == -1)
            lastAppeared[novel[i]].first = i;
        
    std::sort(lastAppeared.begin(), lastAppeared.end());

    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < q; ++i)
    {
        int pos;
        scanf("%d", &pos);
        queries.emplace_back(pos, i);
    }
    std::sort(queries.begin(), queries.end());

    std::vector<std::pair<int, int>> answers(q);
    int prevPos = -1;
    std::pair<int, int> prevAnswer = {1, 0};
    for (auto query : queries)
    {
        int currPos = query.first;
        int start = prevPos + 1;
        int steps = currPos - prevPos;
        
        while (steps > 0 && prevAnswer.first != -1)
        {
            int remainingInRow = countAvailable(prevAnswer.first, prevAnswer.second+1, m);
            
            if (steps > remainingInRow)
            {
                steps -= remainingInRow;
                ++prevAnswer.first;
                prevAnswer.second = 0;
            }
            else
            {
                int left = prevAnswer.second, right = m;
            }
        }

        answers[query.second] = prevAnswer;
    }

    return 0;
}