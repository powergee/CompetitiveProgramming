#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int n, m, chCount;
std::set<std::pair<int, int>> shell;
bool visited[100][100];
bool cheese[100][100];

bool IsValid(int row, int col)
{
    return 0 <= row && row < n && 0 <= col && col < m;
}

void DFS(int row, int col)
{
    if (!IsValid(row, col) || visited[row][col])
        return;

    if (cheese[row][col])
    {
        shell.insert({ row, col });
        return;
    }
    visited[row][col] = true;

    DFS(row + 1, col);
    DFS(row, col + 1);
    DFS(row - 1, col);
    DFS(row, col - 1);
}

bool IsMelting(int row, int col)
{
    int count = 0;
    count += (IsValid(row + 1, col) && visited[row + 1][col] ? 1 : 0);
    count += (IsValid(row, col + 1) && visited[row][col + 1] ? 1 : 0);
    count += (IsValid(row - 1, col) && visited[row - 1][col] ? 1 : 0);
    count += (IsValid(row, col - 1) && visited[row][col - 1] ? 1 : 0);
    return count >= 2;
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < m; ++col)
        {
            int ch;
            scanf("%d", &ch);
            if (ch == 1)
            {
                cheese[row][col] = true;
                ++chCount;
            }
        }
    }

    int time = 0;
    DFS(0, 0);

    while (!shell.empty())
    {
        std::vector<std::pair<int, int>> melting;
        ++time;
        for (auto shPoint : shell)
        {
            if (IsMelting(shPoint.first, shPoint.second))
            {
                cheese[shPoint.first][shPoint.second] = false;
                melting.push_back(shPoint);
            }
        }

        for (auto m : melting)
        {
            shell.erase(m);
            DFS(m.first, m.second);
        }
    }

    printf("%d", time);

    return 0;
}