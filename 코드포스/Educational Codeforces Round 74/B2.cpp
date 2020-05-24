#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define DEAD -100001;

std::set<int> monsters;

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
            int num;
            scanf("%d", &num);
            monsters.insert(num);
        }

        std::vector<int> v(monsters.begin(), monsters.end());
        std::sort(v.begin(), v.end());
        n = v.size();

        int count = 0;
        while (true)
        {
            ++count;

            if (n == 1)
            {
                break;
            }
            else
            {
                v[n-1] = DEAD;

                for (int i = 0; i < n-1; ++i)
                {
                    v[i] -= r;
                }

                if (v[n - 2] <= 0)
                    break;

                --n;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}