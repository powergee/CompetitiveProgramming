#include <iostream>
#include <algorithm>

int width, height, count;
bool map[50][50];
bool visited[50][50];

const std::pair<int, int> DIRS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool Available(int x, int y)
{
    return 0 <= x && x < width && 0 <= y && y < height;
}

void DFS(int x, int y)
{
    visited[x][y] = true;

    for (int i = 0; i < 4; ++i)
    {
        int dx = DIRS[i].first;
        int dy = DIRS[i].second;
        if (Available(x+dx, y+dy) && !visited[x+dx][y+dy] && map[x+dx][y+dy])
            DFS(x+dx, y+dy);
    }
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