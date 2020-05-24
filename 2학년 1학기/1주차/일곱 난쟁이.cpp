#include <iostream>
#include <algorithm>

int main()
{
    int arr[9];
    int sum = 0;

    for (int i = 0; i < 9; ++i)
    {
        scanf("%d", arr + i);
        sum += arr[i];
    }
    std::sort(arr, arr + 9);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = i + 1; j < 9; ++j)
        {
            if (sum - arr[i] - arr[j] == 100)
            {
                for (int k = 0; k < 9; ++k)
                    if (k != i && k != j)
                        printf("%d\n", arr[k]);
                return 0;
            }
        }
    }

    return 0;
}