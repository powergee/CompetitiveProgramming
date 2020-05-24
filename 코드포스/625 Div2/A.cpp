#include <iostream>

int canSolve[2][100];
int p[100];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &canSolve[i][j]);

    int sum = 0;
    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; ++i)
    {
        if (canSolve[0][i] == canSolve[1][i])
            ++sum;
        else
            canSolve[0][i] ? ++count1 : ++count2;
    }

    if (count1 == 0)
        printf("-1");
    else
    {
        int point = 1;
        double ratio = (double)count2 / count1;
        while (point <= ratio)
            ++point;
        //printf("%d %d %d %d\n", sum, count1, count2, point);
        printf("%d", point);
    }

    return 0;
}