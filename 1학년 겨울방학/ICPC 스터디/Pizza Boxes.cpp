#include <iostream>

bool sig1[1000][1000];
bool sig2[1000][1000];
int grid[1000][1000];
int height, width;

void CheckRow(int row)
{
    int maxVal = grid[row][0];
    int maxIndex = 0;
    sig1[row][0] = true;

    for (int col = 0; col < width; ++col)
    {
        if (maxVal < grid[row][col])
        {
            maxVal = grid[row][col];
            sig1[row][maxIndex] = false;
            sig1[row][col] = true;
            maxIndex = col;
        }
    }
}

void CheckCol(int col)
{
    int maxVal = grid[0][col];
    int maxIndex = 0;
    sig2[0][col] = true;

    for (int row = 0; row < height; ++row)
    {
        if (maxVal < grid[row][col])
        {
            maxVal = grid[row][col];
            sig2[maxIndex][col] = false;
            sig2[row][col] = true;
            maxIndex = row;
        }
    }
}

int main()
{
    scanf("%d %d", &height, &width);

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            scanf("%d", &grid[row][col]);
        }
    }

    for (int row = 0; row < height; ++row)
        CheckRow(row);
    
    for (int col = 0; col < width; ++col)
        CheckCol(col);

    long long result = 0;
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (!sig1[row][col] && !sig2[row][col])
                result += grid[row][col];
        }
    }

    printf("%lld", result);

    return 0;
}