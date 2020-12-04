#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        bool scheduled[101] = {false,};
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i)
        {
            int num;
            scanf("%d", &num);
            scheduled[num] = true;
        }

        int answer = 0;
        for (int i = 0; i < m; ++i)
        {
            int num;
            scanf("%d", &num);
            if (scheduled[num])
                ++answer;
        }

        printf("%d\n", answer);
    }

    return 0;
}