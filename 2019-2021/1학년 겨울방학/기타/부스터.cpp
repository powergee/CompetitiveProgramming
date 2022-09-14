#include <iostream>
#include <algorithm>

int N, Q;
int a, b, hp;
std::pair<int, int> checks[250001];
bool visited[250001];

bool IsConnected(int ch1, int ch2)
{
    return hp >= abs(checks[ch1].first - checks[ch2].first) ||
           hp >= abs(checks[ch1].second - checks[ch2].second);
}

bool DFS(int start)
{
    if (visited[start])
        return false;

    if (start == b)
        return true;

    visited[start] = true;

    for (int next = 1; next <= N; ++next)
    {
        if (start != next && !visited[next] && IsConnected(start, next))
            if (DFS(next))
                return true;
    }

    return false;
}

int main()
{
    scanf("%d %d", &N, &Q);

    for (int i = 1; i <= N; ++i)
        scanf("%d %d", &checks[i].first, &checks[i].second);

    while (Q--)
    {
        scanf("%d %d %d", &a, &b, &hp);
        std::fill(visited, visited + N + 1, false);

        if (DFS(a))
            printf("YES\n");
        else printf("NO\n");

    }

    return 0;
}