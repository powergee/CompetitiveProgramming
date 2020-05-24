#include <iostream>

int sum[1025][1025];

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int row = 1; row <= N; ++row)
    {
        for (int col = 1; col <= N; ++col)
        {
            int num;
            scanf("%d", &num);
            sum[row][col] = sum[row - 1][col] + sum[row][col - 1] - sum[row - 1][col - 1] + num;
        }
    }

    while (M--)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        printf("%d\n", sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1]);
    }

    return 0;
}