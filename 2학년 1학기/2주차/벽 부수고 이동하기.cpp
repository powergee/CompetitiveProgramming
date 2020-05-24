#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

struct QueueEle
{
    int row, col, dist, breaked;
};

int rowCount, colCount;
bool map[1000][1000];
bool visited[2][1000][1000];
std::pair<int, int> DIRS[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool IsValid(int r, int c)
{
    return 0 <= r && r < rowCount && 0 <= c && c < colCount;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> rowCount >> colCount;

    for (int row = 0; row < rowCount; ++row)
    {
        std::string line;
        std::cin >> line;
        for (int col = 0; col < colCount; ++col)
            map[row][col] = (line[col] == '1');
    }

    std::fill(&visited[0][0][0], &visited[0][0][0] + sizeof(visited) / sizeof(bool), false);
    
    std::queue<QueueEle> q;
    q.push({0, 0, 1, 0});

    int dist = -1;
    while (!q.empty())
    {
        QueueEle now = q.front();
        q.pop();

        if (visited[now.breaked][now.row][now.col])
            continue;
        visited[now.breaked][now.row][now.col] = true;

        if (now.row == rowCount - 1 && now.col == colCount - 1)
        {
            dist = now.dist;
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nextRow = now.row + DIRS[i].first;
            int nextCol = now.col + DIRS[i].second;

            if (IsValid(nextRow, nextCol))
            {
                if (map[nextRow][nextCol])
                {
                    if (!now.breaked && !visited[now.breaked + 1][nextRow][nextCol])
                        q.push({nextRow, nextCol, now.dist + 1, now.breaked + 1});
                }
                else
                {
                    if (!visited[now.breaked][nextRow][nextCol])
                        q.push({nextRow, nextCol, now.dist + 1, now.breaked});
                }
            }
        }
    }

    printf("%d", dist);

    return 0;
}