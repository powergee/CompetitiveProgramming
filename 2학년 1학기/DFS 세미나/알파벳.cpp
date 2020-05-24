#include <iostream>
#include <algorithm>

int r, c;
bool passed[26];
int map[20][20];

bool Available(int row, int col)
{
    return 0 <= row && row < r && 0 <= col && col < c;
}

const std::pair<int, int> DIRS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int GetMaxDist(int row, int col)
{
    passed[map[row][col]] = true;

    int maxDist = 1;
    for (int i = 0; i < 4; ++i)
    {
        int dr = DIRS[i].first;
        int dc = DIRS[i].second;
        if (Available(row+dr, col+dc) && !passed[map[row+dr][col+dc]])
        {
            int dist = GetMaxDist(row+dr, col+dc) + 1;
            maxDist = std::max(maxDist, dist);
        }
    }

    passed[map[row][col]] = false;
    return maxDist;
}

int main()
{
    scanf("%d %d", &r, &c);

    char line[21];
    for (int i = 0; i < r; ++i)
    {
        scanf("%s", line);
        for (int j = 0; j < c; ++j)
            map[i][j] = (int)(line[j] - 'A');
    }

    printf("%d", GetMaxDist(0, 0));

    return 0;
}