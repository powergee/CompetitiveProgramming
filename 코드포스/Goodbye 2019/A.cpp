#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, k1, k2;
        scanf("%d %d %d", &n, &k1, &k2);

        int max1 = -1, max2 = -1;

        for (int i = 0; i < k1; ++i)
        {
            int input;
            scanf("%d", &input);

            max1 = std::max(max1, input);
        }

        for (int i = 0; i < k2; ++i)
        {
            int input;
            scanf("%d", &input);

            max2 = std::max(max2, input);
        }

        if (max1 > max2)
            printf("YES\n");

        else
            printf("NO\n");
    }
}