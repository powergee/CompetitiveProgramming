#include <iostream>
#include <cmath>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        int eightCount = (int)ceil((double)n / 4);
        for (int i = 0; i < n - eightCount; ++i)
            printf("9");
        while (eightCount--)
            printf("8");
        printf("\n");
    }

    return 0;
}