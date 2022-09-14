#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <tuple>

int n, m;
int map[300][300];
bool visited[300][300];
std::set<std::pair<int, int>> ice;

bool IsValid(int r, int c)
{
    return 0 <= r && r < n && 0 <= c && c < m;
}

int DFS(int r, int c)
{
    if (visited[r][c])
        return 0;

    visited[r][c] = true;

    int result = 1;
    if (IsValid(r + 1, c) && !visited[r + 1][c] && map[r + 1][c] > 0)
        result += DFS(r + 1, c);

    if (IsValid(r - 1, c) && !visited[r - 1][c] && map[r - 1][c] > 0)
        result += DFS(r - 1, c);

    if (IsValid(r, c + 1) && !visited[r][c + 1] && map[r][c + 1] > 0)
        result += DFS(r, c + 1);

    if (IsValid(r, c - 1) && !visited[r][c - 1] && map[r][c - 1] > 0)
        result += DFS(r, c - 1);

    return result;
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &map[i][j]);
            if (map[i][j])
                ice.insert({ i, j });
        }
    }


    int time = 0;
    while (!ice.empty())
    {
        ++time;
        std::vector<std::tuple<int, int, int>> meltAmount;
        std::vector<std::pair<int, int>> melted;
        for (auto it = ice.begin(); it != ice.end(); ++it)
        {
            int melt = 0;
            int r = it->first;
            int c = it->second;
            if (IsValid(r + 1, c) && map[r + 1][c] == 0)
                ++melt;
            if (IsValid(r - 1, c) && map[r - 1][c] == 0)
                ++melt;
            if (IsValid(r, c + 1) && map[r][c + 1] == 0)
                ++melt;
            if (IsValid(r, c - 1) && map[r][c - 1] == 0)
                ++melt;
            meltAmount.emplace_back(r, c, melt);
        }

        for (auto amount : meltAmount)
        {
            int r, c, a;
            std::tie(r, c, a) = amount;
            map[r][c] = std::max(0, map[r][c] - a);
            if (map[r][c] == 0)
                melted.emplace_back(r, c);
        }

        for (auto pos : melted)
            ice.erase(pos);

        if (!ice.empty())
        {
            std::fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
            int r = ice.begin()->first;
            int c = ice.begin()->second;
            if (DFS(r, c) != (int)ice.size())
                break;
        }
    }

    if (ice.empty())
        printf("0");
    else printf("%d", time);

    return 0;
}