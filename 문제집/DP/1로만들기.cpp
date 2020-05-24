#include <iostream>
#include <algorithm>

int memo[1000001];

int MakeOne(int num);

int main()
{
    int input;
    scanf("%d", &input);

    std::fill(memo, memo + 1000001, -1);

    printf("%d", MakeOne(input));

    return 0;
}

int MakeOne(int num)
{
    if (num <= 1)
        return 0;

    int& result = memo[num];
    if (result != -1)
        return result;

    int minResult = 0x7fffffff;
    int temp;
    if (num % 3 == 0)
    {
        temp = MakeOne(num / 3) + 1;
        if (temp < minResult)
            minResult = temp;
    }

    if (num % 2 == 0)
    {
        temp = MakeOne(num / 2) + 1;
        if (temp < minResult)
            minResult = temp;
    }

    temp = MakeOne(num - 1) + 1;
    if (temp < minResult)
        minResult = temp;

    return result = minResult;
}