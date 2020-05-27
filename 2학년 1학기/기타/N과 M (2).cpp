#include <iostream>

int n, m;
int answer[9];

void PrintAll(int start)
{
    if (start >= m + 1)
    {
        for (int i = 1; i <= m; ++i)
            printf("%d ", answer[i]);
        printf("\n");
        return;
    }

    for (int now = answer[start - 1] + 1; now <= n; ++now)
    {
        answer[start] = now;
        PrintAll(start + 1);
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    PrintAll(1);
    return 0;
}