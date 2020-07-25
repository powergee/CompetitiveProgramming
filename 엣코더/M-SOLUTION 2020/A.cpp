#include <iostream>

int main()
{
    int x;
    scanf("%d", &x);

    if (1800 <= x)
        printf("1");
    else if (1600 <= x)
        printf("2");
    else if (1400 <= x)
        printf("3");
    else if (1200 <= x)
        printf("4");
    else if (1000 <= x)
        printf("5");
    else if (800 <= x)
        printf("6");
    else if (600 <= x)
        printf("7");
    else if (400 <= x)
        printf("8");
}