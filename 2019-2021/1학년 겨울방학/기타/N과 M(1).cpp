#include <iostream>
#include <algorithm>

int N, M;
int current[8];

bool IsUsed(int num, int lastIndex)
{
    if (lastIndex < 0)
        return false;

    for (int i = 0; i <= lastIndex; ++i)
        if (current[i] == num)
            return true;

    return false;
}

void Print(int depth)
{
    if (depth == M)
    {
        for (int i = 0; i < M; ++i)
            printf("%d ", current[i]);
        printf("\n");
        return;
    }

    for (int num = 1; num <= N; ++num)
    {
        if (!IsUsed(num, depth - 1))
        {
            current[depth] = num;
            Print(depth + 1);
        }
    }
}

int main()
{
    scanf("%d %d", &N, &M);
    Print(0);
    return 0;
}