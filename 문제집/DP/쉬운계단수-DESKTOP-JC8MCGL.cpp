#include <iostream>
#include <algorithm>
#define DIVIDE 1000000000

int memo[10][100];
int Count(int capacity, int remain);

int main()
{
    int N;
    scanf("%d", &N);
    std::fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(int), -1);

    int sum = 0;
    for (int i = 0; i < 9; ++i)
    {
        sum += Count(i, N - 1);
        sum %= DIVIDE;
    }

    printf("%d", sum);

    return 0;
}

int Count(int capacity, int remain)
{
    if (remain == 0)
        return 1;
    
    int& result = memo[capacity][remain];
    if (result != -1)
        return result;

    if (capacity == 0)
        return result = Count(9, remain);

    result = Count(capacity - 1, remain - 1);
    result %= DIVIDE;
    
    if (9 - capacity > 0)
    {
        result += Count((9 - capacity) - 1, remain - 1);
        result %= DIVIDE;
    }

    return result;
}