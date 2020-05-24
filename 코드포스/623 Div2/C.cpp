#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

int b[100];
bool used[201];
int pair[201];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::fill(used, used + 201, false);

        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
        {
            int input;
            scanf("%d", &input);
            b[i] = input;
            used[input] = true;
        }

        bool success = true;
        for (int i = 0; i < n; ++i)
        {
            bool found = false;
            for (int j = b[i]; j <= 2*n; ++j)
            {
                if (!used[j])
                {
                    used[j] = true;
                    pair[b[i]] = j;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                success = false;
                break;
            }
        }

        if (success)
        {
            for (int i = 0; i < n; ++i)
            {
                printf("%d %d ", std::min(b[i], pair[b[i]]), std::max(b[i], pair[b[i]]));
            }
            printf("\n");
        }
        else
        {
            printf("-1\n");
        }
    }

    return 0;
}