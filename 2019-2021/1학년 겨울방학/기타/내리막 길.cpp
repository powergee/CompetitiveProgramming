#include <iostream>
#include <algorithm>

typedef long long Long;
int width, height;
int diff[500][500];
Long dp[500][500];

bool Valid(int row, int col)
{
    return 0 <= row && row < height && 0 <= col && col <= width;
}

Long Count(int row, int col)
{
    if (row == height - 1 && col == width - 1)
        return 1;

    Long& result = dp[row][col];
    if (result != -1)
        return result;

    result = 0;
    if (Valid(row - 1, col) && diff[row][col] > diff[row - 1][col])
        result += Count(row - 1, col);
    if (Valid(row + 1, col) && diff[row][col] > diff[row + 1][col])
        result += Count(row + 1, col);
    if (Valid(row, col - 1) && diff[row][col] > diff[row][col - 1])
        result += Count(row, col - 1);
    if (Valid(row, col + 1) && diff[row][col] > diff[row][col + 1])
        result += Count(row, col + 1);

    return result;
}

int main()
{
    scanf("%d %d", &height, &width);

    for (int r = 0; r < height; ++r)
        for (int c = 0; c < width; ++c)
            scanf("%d", &diff[r][c]);
            
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1);
    printf("%lld", Count(0, 0));
    return 0;
}