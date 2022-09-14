#include <iostream>
#include <algorithm>

int width, height, count;
bool map[50][50];
bool visited[50][50];

bool Available(int x, int y)
{
    return 0 <= x && x < width && 0 <= y && y < height;
}

void DFS(int x, int y)
{
    visited[x][y] = true;

    if (Available(x - 1, y) && !visited[x - 1][y] && map[x - 1][y])
        DFS(x - 1, y);
    if (Available(x + 1, y) && !visited[x + 1][y] && map[x + 1][y])
        DFS(x + 1, y);
    if (Available(x, y - 1) && !visited[x][y - 1] && map[x][y - 1])
        DFS(x, y - 1);
    if (Available(x, y + 1) && !visited[x][y + 1] && map[x][y + 1])
        DFS(x, y + 1);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(bool), false);
        std::fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(bool), false);
        scanf("%d %d %d", &width, &height, &count);

        for (int i = 0; i < count; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            map[x][y] = true;
        }

        int result = 0;
        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                if (map[x][y] && !visited[x][y])
                {
                    DFS(x, y);
                    ++result;
                }
            }
        }

        printf("%d\n", result);
    }

    return 0;
}