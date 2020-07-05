#include <iostream>

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d", (n % 1000 == 0 ? 0 : 1000 - (n % 1000)));

    return 0;
}