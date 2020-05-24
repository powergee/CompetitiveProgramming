#include <iostream>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int score;
            scanf("%d", &score);
            sum += score;
        }

        printf("%d\n", std::min(m, sum));
    }

    return 0;
}