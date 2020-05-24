#include <iostream>
#include <queue>
#include <set>

int main()
{
    int n, k;
    std::queue<std::pair<int, int>> q;
    std::set<int> visited;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        int pos;
        scanf("%d", &pos);
        q.push({pos, 0});
    }

    long long distSum = 0;
    int count = 0;
    while (!q.empty())
    {
        std::pair<int, int> now = q.front();
        q.pop();

        int pos = now.first;
        int dist = now.second;

        if (visited.find(pos) != visited.end())
            continue;

        visited.insert(pos);
        ++count;
        distSum += dist;
        
        if (count == k + n)
            break;

        if (visited.find(pos + 1) == visited.end())
            q.push({pos + 1, dist + 1});

        if (visited.find(pos - 1) == visited.end())
            q.push({pos - 1, dist + 1});
    }

    printf("%lld", distSum);

    return 0;
}