#include <iostream>

void Binary(int num, int depth)
{
    if (num == 1)
        printf("%d\n", depth);

    else 
    {
        if (num % 2 == 1)
            printf("%d ", depth);

        Binary(num / 2, depth + 1);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int input;
        scanf("%d", &input);
        Binary(input, 0);
    }

    return 0;
}