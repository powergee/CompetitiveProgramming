#include <iostream>
#include <algorithm>

int main()
{
    int T;
    std::cin >> T;

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (i == 0 && j == 0)
                    printf("W");
                else printf("B");
            }
            printf("\n");
        }
    }

    return 0;
}