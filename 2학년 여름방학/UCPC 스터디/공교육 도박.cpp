#include <iostream>
#include <algorithm>

typedef long long Long;
int n;
double expDP[7][7][999];
double bestDP[7][7][7][998];

int calcPrize(int a, int b, int c)
{
    if (a == b && b == c)
        return 10000 + 1000*a;
    else if (a == b)
        return 1000 + 100*a;
    else if (b == c)
        return 1000 + 100*b;
    else if (c == a)
        return 1000 + 100*c;
    else
        return 100*std::max(a, std::max(b, c));
}

double getExpected(int a, int b, int remaining)
{
    if (remaining == 0)
        return 0;

    double &result = expDP[a][b][remaining];
    if (result != 0)
        return result;

    double sum = 0;
    for (int next = 1; next <= 6; ++next)
        sum += std::max((double)calcPrize(a, b, next), getExpected(b, next, remaining - 1));
    return result = sum / 6;
}

double getBestResult(int a, int b, int c, int remaining)
{
    double& result = bestDP[a][b][c][remaining];
    if (result != 0)
        return result;

    int current = calcPrize(a, b, c);
    if (remaining == 0)
        return result = current;
        
    double exp = getExpected(b, c, remaining);
    if (current > exp)
        return result = current;

    double sum = 0;
    for (int d = 1; d <= 6; ++d)
        sum += getBestResult(b, c, d, remaining - 1);
    
    return result = sum / 6;
}

int main()
{
    scanf("%d", &n);
    double sum = 0;
    for (int a = 1; a <= 6; ++a)
        for (int b = 1; b <= 6; ++b)
            for (int c = 1; c <= 6; ++c)
                sum += getBestResult(a, b, c, n - 3);

    printf("%.10lf", sum / 216);

    return 0;
}