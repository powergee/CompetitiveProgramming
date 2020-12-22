#include <iostream>
#include <algorithm>

int main()
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    printf("%d", std::min(a, std::min(b, std::min(c, d))));

    return 0;
}