#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <string>

int D(int n)
{
    return (2 * n) % 10000;
}

int S(int n)
{
    return n == 0 ? 9999 : n - 1;
}

int L(int n)
{
    int msb = n / 1000;
    return (n - msb * 1000) * 10 + msb;
}

int R(int n)
{
    int lsb = n % 10;
    return lsb * 1000 + n / 10;
}

std::vector<std::pair<int, char>> graph[10000];
std::pair<int, char> prev[10000];

int main()
{
    for (int i = 0; i < 10000; ++i)
    {
        graph[i].push_back({ D(i), 'D' });
        graph[i].push_back({ S(i), 'S' });
        graph[i].push_back({ L(i), 'L' });
        graph[i].push_back({ R(i), 'R' });
    }

    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::fill(prev, prev + 10000, std::make_pair(-1, '\0'));

        int a, b;
        scanf("%d %d", &a, &b);

        std::queue<int> q;
        q.push(a);
        prev[a].first = a;

        while (!q.empty())
        {
            int now = q.front();
            q.pop();

            if (now == b)
                break;

            for (auto next : graph[now])
            {
                if (prev[next.first].first == -1)
                {
                    prev[next.first] = std::make_pair(now, next.second);
                    q.push(next.first);
                }
            }
        }

        std::stack<char> path;
        for (int i = b; prev[i].first != i; i = prev[i].first)
            path.push(prev[i].second);

        while (!path.empty())
        {
            putchar(path.top());
            path.pop();
        }
        putchar('\n');
    }

    return 0;
}