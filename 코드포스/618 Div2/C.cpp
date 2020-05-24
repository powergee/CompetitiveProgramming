#include <iostream>
#include <algorithm>
#include <functional>

typedef unsigned int uint;

int count[32];

int main()
{
    int n;
    scanf("%d", &n);

    int arr[100000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", arr + i);

        for (int j = 0; j < 32; ++j)
        {
            uint bit = 1 << j;
            if (arr[i] & bit)
                ++count[j];
        }
    }

    int maxVal = 0;
    int first = 0;
    for (int i = 0; i < n; ++i)
    {
        int val = 0;
        
        for (int j = 0; j < 32; ++j)
        {
            uint bit = 1 << j;
            if (count[j] == 1 && arr[i] & bit)
                val += bit;
        }

        if (maxVal < val)
        {
            maxVal = val;
            first = i;
        }
    }

    printf("%d ", arr[first]);
    bool pass = true;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] == arr[first] && pass)
        {
            pass = false;
            continue;
        }

        printf("%d ", arr[i]);
    }

    return 0;
}