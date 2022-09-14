#include <iostream>
#include <algorithm>

int dp[301][301];

int Divide(int width, int height)
{
    if (width <= 0 || height <= 0)
        return 0;

    if (width == 1)
        return height - 1;
    
    if (height == 1)
        return width - 1;

    int& result = dp[width][height];
    if (result != -1)
        return result;

    int widthHalf = width / 2;
    int heightHalf = height / 2;
    return result = std::min(Divide(widthHalf, height) + Divide(width - widthHalf, height) + 1,
                            Divide(width, heightHalf) + Divide(width, height - heightHalf) + 1);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);

    printf("%d", Divide(N, M));

    return 0;
}