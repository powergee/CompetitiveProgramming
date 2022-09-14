#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> sqares;
int memo[100001];

bool IsSquare(unsigned int num)
{
    unsigned int temp;
    switch (num & 0x0f) {
    case 0:
    case 1:
    case 4:
    case 9:
        temp = (unsigned int)(sqrt((double)num)+0.5);
        return temp*temp == num;
     
    default:
        return false;
    }
}

inline int Pow2(int n)
{
    return n * n;
}

int Count(int num)
{
    if (memo[num] != 0)
        return memo[num];

    if (IsSquare(num))
        return memo[num] = 1;

    int minCount = 0x7fffffff;

    for (int sq : sqares)
    {
        if (sq > num)
            break;
        minCount = std::min(minCount, Count(num - sq));
    }

    return memo[num] = minCount + 1;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; n > Pow2(i); ++i)
    {
        sqares.push_back(Pow2(i));
    }

    printf("%d", Count(n));

    return 0;
}