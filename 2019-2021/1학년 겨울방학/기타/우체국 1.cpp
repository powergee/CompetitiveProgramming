#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <limits>
#include <cmath>

typedef long long Long;

int V, P;
Long L;
std::vector<Long> pos;

Long GetDist(int a, int b)
{
    return std::min(std::abs(pos[a] - pos[b]), L - std::abs(pos[a] - pos[b]));
}

int main()
{
    scanf("%d %d %lld", &V, &P, &L);

    for (int i = 0; i < V; ++i)
    {
        Long input;
        scanf("%lld", &input);
        pos.push_back(input);
    }

    std::vector<bool> select(V);
    std::fill(select.begin(), select.end() - P, false);
    std::fill(select.end() - P, select.end(), true);
    std::stack<int> s;
    std::vector<Long> dist(V);
    std::vector<Long> result;
    Long minDistSum = INT64_MAX;

    do
    {
        std::fill(dist.begin(), dist.end(), INT64_MAX);
        int leftmost = V, rightmost = -1;

        for (int i = 0; i < V; ++i)
        {
            if (select[i])
            {
                leftmost = std::min(leftmost, i);
                rightmost = std::max(rightmost, i);

                dist[i] = 0;
                while (!s.empty())
                {
                    int prev = s.top();
                    s.pop();
                    dist[prev] = std::min(dist[prev], GetDist(prev, i));
                }
            }
            else
                s.push(i);
        }

        while (!s.empty())
        {
            int prev = s.top();
            s.pop();
            dist[prev] = std::min(dist[prev], GetDist(prev, leftmost));
        }

        for (int i = V - 1; i >= 0; --i)
        {
            if (select[i])
            {
                dist[i] = 0;
                while (!s.empty())
                {
                    int prev = s.top();
                    s.pop();
                    dist[prev] = std::min(dist[prev], GetDist(prev, i));
                }
            }
            else
                s.push(i);
        }

        while (!s.empty())
        {
            int prev = s.top();
            s.pop();
            dist[prev] = std::min(dist[prev], GetDist(prev, rightmost));
        }

        Long distSum = 0;
        for (int i = 0; i < V; ++i)
            distSum += dist[i];

        if (minDistSum > distSum)
        {
            minDistSum = distSum;
            result.clear();
            for (int i = 0; i < V; ++i)
            {
                if (select[i])
                    result.push_back(pos[i]);
            }
        }

    } while (std::next_permutation(select.begin(), select.end()));

    printf("%lld\n", minDistSum);
    for (Long post : result)
        printf("%lld ", post);

    return 0;
}