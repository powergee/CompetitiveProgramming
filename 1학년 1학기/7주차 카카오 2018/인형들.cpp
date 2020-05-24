#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

int n, k;
double arr[500];
double sumMemo[500];

void InitMemo()
{
    double sum = 0;

    for (int i = 0; i < n; ++i)
    {
        sum += arr[i];
        sumMemo[i] = sum;
    }
}

double Average(int start, int last)
{
    double sum;

    if (start - 1 >= 0)
        sum = sumMemo[last] - sumMemo[start - 1];
    else sum = sumMemo[last];

    return sum / (double)(last - start + 1);
}

double Variance(int start, int last)
{
    double m = Average(start, last);
    double sum = 0;

    for (int i = start; i <= last; ++i)
    {
        sum += pow(arr[i] - m, 2);
    }

    return sum / (double)(last - start + 1);
}

double StdDev(int start, int last)
{
    return sqrt(Variance(start, last));
}

int main ()
{
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &arr[i]);
    }

    InitMemo();

    double stddev = StdDev(0, k-1);

    for (; k <= n; ++k)
    {
        for (int i = 0; i+k-1 < n; ++i)
        {
            stddev = min(stddev, StdDev(i, i+k-1));
        }
    }

    printf("%.10lf", stddev);

    return 0;
}