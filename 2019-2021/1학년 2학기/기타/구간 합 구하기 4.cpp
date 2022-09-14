#include <iostream>

int N, M;
int sum[100001];

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i)
    {
        int num;
        scanf("%d", &num);
        sum[i] = sum[i - 1] + num;
    }

    while (M--)
    {
        int i, j;
        scanf("%d %d", &i, &j);

        printf("%d\n", sum[j] - sum[i - 1]);
    }

    return 0;
}