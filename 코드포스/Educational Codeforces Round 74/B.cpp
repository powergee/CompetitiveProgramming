#include <iostream>
#include <algorithm>
#define DEAD -100001

int pos[100000];

int main()
{
    int q;
    scanf("%d", &q);

    while (q--)
    {
        int n, r;
        scanf("%d %d", &n, &r);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &pos[i]);
        }

        std::sort(pos, pos + n);

        int count = 0;
        while (true)
        {
            ++count;

            int lastPos = pos[n-1];
            pos[n-1] = DEAD;
            for (int i = n - 1; i >= 0; --i, --n)
            {
                if (pos[i] == lastPos)
                    pos[i] = DEAD;
                if (pos[i] != lastPos)
                    break;
            }

            for (int i = 0; i < n-1; ++i)
            {
                pos[i] -= r;
            }

            if (pos[n - 2] <= 0)
                break;

            --n;
        }

        printf("%d\n", count);
    }

    return 0;
}