#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int arr[100];
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);

        bool yes = true;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (abs(arr[i] - arr[j]) % 2 == 1)
                    yes = false;

                if (!yes) goto END;
            }
        } END:

        printf("%s\n", (yes ? "YES" : "NO"));
    }

    return 0;
}