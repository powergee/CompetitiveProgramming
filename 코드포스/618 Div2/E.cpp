#include <iostream>
#include <algorithm>

int n;
double arr[1000000];

bool IsAscending()
{
    for (int i = 0; i < n - 1; ++i)
        if (arr[i] > arr[i + 1])
            return false;

    return true;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int input;
        scanf("%d", &input);
        arr[i] = input;
    }

    while (!IsAscending())
    {
        int prevStart = 0;
        double subSum = arr[0];
        for (int i = 1; i < n; ++i)
        {
            if (arr[i - 1] < arr[i])
            {
                double val = subSum / (i - prevStart);
                std::fill(arr + prevStart, arr + i, val);
                prevStart = i;
                subSum = arr[i];
            }
            else
            {
                subSum += arr[i];
            }
        }

        double val = subSum / (n - prevStart);
        std::fill(arr + prevStart, arr + n, val);
    }

    for (int i = 0; i < n; ++i)
        printf("%.9lf\n", arr[i]);

    return 0;
}