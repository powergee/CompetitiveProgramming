#include <iostream>
#include <algorithm>
#include <queue>

std::pair<int, int> cates[200000];
int n;

int GetLast(int start)
{
    int count = cates[start].first;
    int pos = start;
    while (pos + 1 < n && cates[pos + 1].first == count)
        ++pos;
    return pos;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &cates[i].first);
    for (int i = 0; i < n; ++i)
        scanf("%d", &cates[i].second);

    long long sum = 0;
    std::sort(cates, cates + n);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    std::queue<std::pair<int, int>> remain;
    
    for (int i = 0; i < n; ++i)
    {
        int qSize = q.size();
        for (int j = 0; j < qSize; ++j)
        {
            std::pair<int, int> p = q.top();
            q.pop();

            if (p.first < cates[i].first)
                continue;

            else if (p.first == cates[i].first)
            {
                if (p.second <= cates[i].second)
                {
                    sum += p.second;
                    ++p.first;
                }
                else
                {
                    sum += cates[i].second;
                    ++cates[i].first;
                }
            }

            remain.push(p);
        }

        while (!remain.empty())
        {
            q.push(remain.front());
            remain.pop();
        }

        q.push(cates[i]);
    }

    printf("%lld", sum);

    return 0;
}