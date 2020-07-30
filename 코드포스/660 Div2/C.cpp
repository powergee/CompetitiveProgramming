#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;
Long popul[100000];
Long happ[100000];
Long passed[100000];
Long good[100000], bad[100000];
std::vector<int> graph[100000];
int parent[100000];
bool visited[100000];

Long initPassed(int city)
{
    visited[city] = true;
    Long result = popul[city];
    for (int next : graph[city])
    {
        if (!visited[next])
        {
            result += initPassed(next);
            parent[next] = city;
        }
    }
    
    return passed[city] = result;
}

bool goodAndBadAreValid(int city)
{
    visited[city] = true;
    bool hasChild = false;
    Long childGood = 0, childBad = 0;
    for (int next : graph[city])
    {
        if (!visited[next])
        {
            childGood += good[next];
            childBad += bad[next];
            hasChild = true;
        }
    }

    if (!hasChild)
        return true;

    if (passed[city]-popul[city] != childGood+childBad)
        return false;
    
    Long sleptGood = std::max(popul[city] - bad[city], 0LL);
    if (good[city]-sleptGood < childGood)
        return false;
    
    Long sleptBad = popul[city] - sleptGood;
    if (bad[city] - sleptBad < 0 || bad[city] - sleptBad > childBad)
        return false;

    bool result = true;
    for (int next : graph[city])
    {
        if (!visited[next])
            result = goodAndBadAreValid(next);
        
        if (!result)
            break;
    }

    return result;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        std::fill(visited, visited+n, false);
        std::fill(parent, parent+n, -1);

        for (int i = 0; i < n; ++i)
            graph[i].resize(0);

        for (int i = 0; i < n; ++i)
            scanf("%lld", popul+i);
        
        for (int i = 0; i < n; ++i)
            scanf("%lld", happ+i);
        
        for (int i = 0; i < n-1; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);

            graph[u-1].push_back(v-1);
            graph[v-1].push_back(u-1);
        }

        initPassed(0);
        bool yes = true;
        for (int i = 0; i < n && yes; ++i)
        {
            good[i] = (passed[i]+happ[i])/2;
            bad[i] = (passed[i]-happ[i])/2;

            if (good[i] < 0 || bad[i] < 0 || good[i]+bad[i] != passed[i])
                yes = false;
        }

        std::fill(visited, visited+n, false);
        if (!goodAndBadAreValid(0))
            yes = false;

        if (yes)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}