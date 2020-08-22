#include <iostream>
#include <algorithm>

int n, k, m;
int endOfPole[1500];
int below[7000];
int next[7000];
int nodeCount;
int maxNodeCount;
int dp[7000][7000];

// from에서 아래로 내려감.
int getMinCount(int from, int to)
{
    int& result = dp[from][to];
    if (result != -1)
        return result;

    if (from == to || below[from] == to)
        return result = 0;
    if (below[below[from]] == -1)
        return result = 1e9;

    return result = std::min(getMinCount(below[from], to)+1,
        getMinCount(next[below[from]], to));
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d\n", t);
        scanf("%d %d %d", &n, &k, &m);
        maxNodeCount = 2*n+2*k;

        for (int i = 0; i < maxNodeCount; ++i)
            for (int j = 0; j < maxNodeCount; ++j)
                dp[i][j] = -1;

        nodeCount = 0;
        for (int i = 0; i < n; ++i)
        {
            endOfPole[i] = nodeCount++;
            next[i] = -1;
        }

        for (int i = 0; i < k; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);

            int uNode = nodeCount++;
            int vNode = nodeCount++;
            below[endOfPole[u-1]] = uNode;
            below[endOfPole[v-1]] = vNode;
            endOfPole[u-1] = uNode;
            endOfPole[v-1] = vNode;
            next[uNode] = vNode;
            next[vNode] = uNode;
        }

        for (int i = 0; i < n; ++i)
        {
            int end = nodeCount++;;
            below[endOfPole[i]] = end;
            endOfPole[i] = end;
            next[end] = -1;
            below[end] = -1;
        }

        int result = 0;
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);

            int from = u-1;
            int to = nodeCount-n+v-1;
            int count = getMinCount(from, to);

            if (count > k)
                --result;
            else
                result += count;
        }

        printf("%d\n", result);
    }

    return 0;
}