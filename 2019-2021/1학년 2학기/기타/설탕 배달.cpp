#include <iostream>

int main()
{
    int N;
    scanf("%d", &N);

    if (N == 4 || N == 7)
        printf("-1");

    else
    {
        switch (N % 5)
        {
        case 0:
            printf("%d", N / 5);
            break;
        case 1:
        case 3:
            printf("%d", N / 5 + 1);
            break;
        case 2:
        case 4:
            printf("%d", N / 5 + 2);
            break;
        }
    }

    return 0;
}