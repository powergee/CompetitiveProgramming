#include <iostream>
#include <cmath>
#include <algorithm>

int n, m;
int c1, c2;

int P[500000];
int Q[500000];

int GetDist(int id1, int id2)
{
    return abs(P[id1] - Q[id2]) + abs(c1 - c2);
}

int GetDist(std::pair<int, int> pq)
{
    return GetDist(pq.first, pq.second);
}

int main()
{
    scanf("%d %d", &n, &m);
    scanf("%d %d", &c1, &c2);

    for (int i = 0; i < n; ++i)
        scanf("%d", P + i);
    
    for (int i = 0; i < m; ++i)
        scanf("%d", Q + i);

    std::pair<int, int> result(0, 0);

    for (int p = 0; p < n; ++p)
    {
        int pVal = P[p];
        int q = std::lower_bound(Q, Q + m, pVal) - Q;

    }

    return 0;
}