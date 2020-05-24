#include <iostream>
#include <algorithm>

long long GetMask(int length)
{
    long long result = 0;
    for (int i = 0; i < length; ++i)
        result += 1<<i;

    return result;
}

int GetLength(long long val)
{
    for (int i = 1;; ++i)
    {
        if (GetMask(i) >= val)
            return i;
    }
}

long long input[400000];

int main()
{
    int n;
    scanf("%d", &n);

    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld", input + i);
        sum += input[i];
    }

    std::sort(input, input + n);

    int len = GetLength(input[n - 1]);
    long long mask = GetMask(len + 1);
    long long result = mask & sum;

    for (int i = 63; i > len; --i)
    {
        if (1<<i & result)
        {
            result -= (1<<i);
            break;
        }
    }

    printf("%lld", result);

    return 0;
}