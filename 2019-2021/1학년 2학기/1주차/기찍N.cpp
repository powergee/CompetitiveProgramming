#include <iostream>

int main()
{
    int n;
    scanf("%d", &n);
    ++n;

    while (--n)
    {
        printf("%d\n", n);
    }

    return 0;
}