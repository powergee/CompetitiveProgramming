#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        if (n == 1)
        {
            printf("0\n");
            continue;
        }

        int two = 0;
        int three = 0;
        bool able = true;
        while (n > 1 && able)
        {
            if (n % 2 == 0)
            {
                ++two;
                n /= 2;
            }
            else if (n % 3 == 0)
            {
                ++three;
                n /= 3;
            }
            else able = false;
        }

        if (able)
        {
            if (two == three)
                printf("%d\n", two);
            else if (two < three)
                printf("%d\n", (three - two) + three);
            else
                printf("-1\n");
        }
        else
        {
            printf("-1\n");
        }
        
    }

    return 0;
}