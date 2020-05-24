#include <iostream>
#include <queue>
#include <set>

int main()
{
    int n, m;
    std::queue<std::pair<int, int>> q;
    std::set<int> occupied;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
    {
        int pos;
        scanf("%d", &pos);
        occupied.insert(pos);
        q.push({pos - 1, 1});
        q.push({pos + 1, 1});
    }

    int count = 0;
    long long sum = 0;
    std::set<int> answer;
    while (!q.empty() && count < m)
    {
        auto now = q.front();
        q.pop();

        if (occupied.find(now.first) != occupied.end())
            continue;
            
        ++count;
        sum += now.second;
        occupied.insert(now.first);
        answer.insert(now.first);

        if (occupied.find(now.first + 1) == occupied.end())
            q.push({now.first + 1, now.second + 1});
        if (occupied.find(now.first - 1) == occupied.end())
            q.push({now.first - 1, now.second + 1});
    }

    printf("%lld\n", sum);
    for (int pos : answer)
        printf("%d ", pos);

    return 0;
}