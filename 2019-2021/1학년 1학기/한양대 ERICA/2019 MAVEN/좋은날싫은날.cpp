#include <iostream>
#include <cmath>
#define BAD 1
#define GOOD 0
using namespace std;

int N;
int mood;
double goodPoss[101];
double badPoss[101];

double gg, gb, bg, bb;

int main()
{
    scanf("%d %d", &N, &mood);

    if (mood == GOOD)
    {
        goodPoss[0] = 1;
        badPoss[0] = 0;
    }
    else
    {
        goodPoss[0] = 0;
        badPoss[0] = 1;
    }

    scanf("%lf %lf %lf %lf", &gg, &gb, &bg, &bb);

    for (int i = 1; i <= N; ++i)
    {
        goodPoss[i] = goodPoss[i - 1] * gg + badPoss[i - 1] * bg;
        badPoss[i] = goodPoss[i - 1] * gb + badPoss[i - 1] * bb;
    }

    printf("%d\n%d", (int)round(goodPoss[N]*1000), (int)round(badPoss[N]*1000));

    return 0;
}