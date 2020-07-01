#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>

void addOnes(int& k, int x, int y, int width, int grid[300][300], std::queue<std::tuple<int, int, int>>& q)
{
    for (int i = 0; i < width; ++i)
    {
        if (grid[x + i][y + i])
            continue;
        grid[x + i][y + i] = 1;
        --k;

        if (k == 0)
            return;
    }

    for (int i = 0; i < width; ++i)
    {
        if (grid[x + width - i - 1][y + i])
            continue;
        grid[x + width - i - 1][y + i] = 1;
        --k;

        if (k == 0)
            return;
    }

    if (width == 1)
        return;

    if (width % 2)
    {
        q.push(std::make_tuple(x, y, width / 2 + 1));
        q.push(std::make_tuple(x + width / 2, y + width / 2, width / 2 + 1));
        q.push(std::make_tuple(x + width / 2, y, width / 2 + 1));
        q.push(std::make_tuple(x, y + width / 2, width / 2 + 1));
    }
    else
    {
        q.push(std::make_tuple(x, y, width / 2));
        q.push(std::make_tuple(x + width / 2, y + width / 2, width / 2));
        q.push(std::make_tuple(x + width / 2, y, width / 2));
        q.push(std::make_tuple(x, y + width / 2, width / 2));
    }
}

int minRow(int width, int grid[300][300])
{
    int result = 1e9;
    for (int i = 0; i < width; ++i)
    {
        int now = 0;
        for (int j = 0; j < width; ++j)
            now += grid[i][j];

        result = std::min(result, now);
    }

    return result;
}

int maxRow(int width, int grid[300][300])
{
    int result = 0;
    for (int i = 0; i < width; ++i)
    {
        int now = 0;
        for (int j = 0; j < width; ++j)
            now += grid[i][j];

        result = std::max(result, now);
    }

    return result;
}

int minCol(int width, int grid[300][300])
{
    int result = 1e9;
    for (int i = 0; i < width; ++i)
    {
        int now = 0;
        for (int j = 0; j < width; ++j)
            now += grid[j][i];

        result = std::min(result, now);
    }

    return result;
}

int maxCol(int width, int grid[300][300])
{
    int result = 0;
    for (int i = 0; i < width; ++i)
    {
        int now = 0;
        for (int j = 0; j < width; ++j)
            now += grid[j][i];

        result = std::max(result, now);
    }

    return result;
}

int grid[300][300];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::fill(&grid[0][0], &grid[0][0] + sizeof(grid) / sizeof(int), 0);
        int n, k;
        scanf("%d %d", &n, &k);

        std::queue<std::tuple<int, int, int>> q;
        q.push(std::make_tuple(0, 0, n));

        while (!q.empty())
        {
            if (k == 0)
                break;

            int x, y, width;
            std::tie(x, y, width) = q.front();
            q.pop();

            addOnes(k, x, y, width, grid, q);
        }

        int dr = maxRow(n, grid) - minRow(n, grid);
        int dc = maxCol(n, grid) - minCol(n, grid);
        printf("%d\n", dr * dr + dc * dc);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                printf("%d", grid[i][j]);
            printf("\n");
        }
    }

    return 0;
}