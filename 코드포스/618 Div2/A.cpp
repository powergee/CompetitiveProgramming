#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int arr[1000];
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);

        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] == 0)
            {
                arr[i] = 1;
                ++count;
            }
        }

        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum += arr[i];

        if (sum == 0)
            ++count;
        printf("%d\n", count);
    }

    return 0;
}