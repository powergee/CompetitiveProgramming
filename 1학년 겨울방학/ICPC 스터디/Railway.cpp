#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

int N, L;
std::pair<int, int> zone[100000];

bool CompareSecond(const std::pair<int, int>& z1, const std::pair<int, int>& z2)
{
    return z1.second < z2.second;
}

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &zone[i].first, &zone[i].second);
        if (zone[i].first > zone[i].second)
            std::swap(zone[i].first, zone[i].second);
    }

    scanf("%d", &L);
    std::sort(zone, zone + N, CompareSecond);
    int answer = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;

    for (int i = 0; i < N; ++i)
    {
        q.push(zone[i].first);

        while (!q.empty() && q.top() < zone[i].second - L)
            q.pop();

        answer = std::max(answer, (int)q.size());
    }

    printf("%d", answer);

    return 0;
}