#include <iostream>

int n, k;
int kit[8];

int Count(int curr, unsigned used, int remain)
{
    if (remain == 0)
        return 1;
    
    int result = 0;
    for (int i = 0; i < n; ++i)
        if (!(used & (1<<i)) && curr + kit[i] >= 0)
            result += Count(curr + kit[i], used + (1<<i), remain - 1);
    
    return result;
}

int main()
{
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", kit + i);
        kit[i] -= k;
    }

    printf("%d", Count(0, 0, n));

    return 0;
}