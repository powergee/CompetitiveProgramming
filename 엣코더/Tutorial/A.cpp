#include <iostream>

int main()
{
    int a, b, c;
    char str[101];
    scanf("%d%d%d%s", &a, &b, &c, str);

    printf("%d %s", a + b + c, str);

    return 0;
}