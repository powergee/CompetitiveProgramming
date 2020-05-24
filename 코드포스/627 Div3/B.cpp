#include <iostream>
#include <algorithm>

int arr[5000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", arr + i);

        bool yes = false;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 2; j < n; ++j)
            {
                if (arr[i] == arr[j])
                    yes = true;

                if (yes) goto END;
            }
        } END:

        printf("%s\n", (yes ? "YES" : "NO"));
    }

    return 0;
}