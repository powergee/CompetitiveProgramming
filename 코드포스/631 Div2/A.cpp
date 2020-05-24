#include <iostream>
#include <algorithm>

int main()
{
    int T;
    std::cin >> T;

    while (T--)
    {
        int n, x;
        bool rank[300] {false,};
        scanf("%d %d", &n, &x);

        for (int i = 0; i < n; ++i)
        {
            int r;
            scanf("%d", &r);
            rank[r] = true;
        }

        int possible;
        int ignored = 0;
        for (possible = 1; possible <= 300; ++possible)
        {
            if (!rank[possible])
                ++ignored;

            if (ignored == x + 1)
            {
                --possible;
                break;
            }
        }

        printf("%d\n", possible);
    }

    return 0;
}