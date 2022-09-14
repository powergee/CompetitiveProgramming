#include <iostream>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (c <= b)
        printf("-1");
    else
        printf("%d", (a+1)/(c-b) + ((a+1)%(c-b) ? 1 : 0));

    return 0;
}