#include <iostream>

int main()
{
    int n;
    scanf("%d", &n);

    int max = -0x7fffffff, min = 0x7fffffff;
    while (n--)
    {
        int input;
        scanf("%d", &input);

        if (input > max)
            max = input;
        if (input < min)
            min = input;
    }

    printf("%d %d", min, max);
}