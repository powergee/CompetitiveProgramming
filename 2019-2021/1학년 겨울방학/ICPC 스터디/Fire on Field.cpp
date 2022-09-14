#include <iostream>

int A[1001];

int main()
{
    A[0] = A[1] = 1;
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; ++i)
    {
        for (int val = 1;; ++val)
        {
            A[i] = val;
            bool success = true;
            for (int k = 1; i - 2 * k >= 0; ++k)
            {
                if (A[i - 2 * k] - A[i - k] == A[i - k] - A[i])
                {
                    success = false;
                    break;
                }
            }

            if (success)
                break;
        }
    }

    printf("%d", A[n]);

    return 0;
}