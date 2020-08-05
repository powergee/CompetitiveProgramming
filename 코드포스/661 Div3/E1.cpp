#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

typedef long long Long;
// u, v, w, count
typedef std::tuple<int, int, Long, Long> Edge;

Edge edges[100000];
std::vector<Edge*> graph[100000];
bool visited[100000];

struct Compare
{
    bool operator()(const Edge* e1, const Edge* e2)
    {
        Long diff1 = std::get<3>(*e1)*(std::get<2>(*e1) - std::get<2>(*e1)/2);
        Long diff2 = std::get<3>(*e2)*(std::get<2>(*e2) - std::get<2>(*e2)/2);
        return diff1 < diff2;
    }
};

Long initCount(int start)
{
    if (visited[start])
        return 0;

    visited[start] = true;
    Long sum = 0;
    bool hasNext = false;
    for (Edge* e : graph[start])
    {
        int u, v;
        Long w, count;
        std::tie(u, v, w, count) = *e;
        int next = (u == start ? v : u);

        if (visited[next])
            continue;

        hasNext = true;

        count = initCount(next);
        sum += count;
        *e = std::make_tuple(u, v, w, count);
    }

    if (!hasNext)
        return 1;
    return sum;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long n, s;
        scanf("%lld %lld", &n, &s);

        for (int i = 0; i < n-1; ++i)
        {
            int u, v;
            Long w;
            scanf("%d %d %lld", &u, &v, &w);
            edges[i] = std::make_tuple(u-1, v-1, w, 0);
            graph[u-1].push_back(edges+i);
            graph[v-1].push_back(edges+i);
        }

        /*printf("before\n");
        for (int i = 0; i < n-1; ++i)
            printf("%d %d %lld %lld\n", std::get<0>(edges[i]), std::get<1>(edges[i]), std::get<2>(edges[i]), std::get<3>(edges[i]));
        printf("\n");*/

        initCount(0);

        /*printf("initCount\n");
        for (int i = 0; i < n-1; ++i)
            printf("%lld\n", std::get<3>(edges[i]));
        printf("\n");*/

        std::priority_queue<Edge*, std::vector<Edge*>, Compare> q;
        Long wSum = 0;
        for (int i = 0; i < n-1; ++i)
        {
            q.push(edges+i);
            wSum += std::get<3>(edges[i]) * std::get<2>(edges[i]);
        }

        int result = 0;
        while (wSum > s)
        {
            ++result;
            Edge* current = q.top();
            int u, v;
            Long w, count;
            std::tie(u, v, w, count) = *current;
            q.pop();

            Long diff = w - w/2;
            wSum -= diff * count;
            *current = std::make_tuple(u, v, w/2, count);
            q.push(current);
        }

        printf("%d\n", result);

        for (int i = 0; i < n; ++i)
            graph[i].clear();
        std::fill(visited, visited+n, false);
    }


    return 0;
}