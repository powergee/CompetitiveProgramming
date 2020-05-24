#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int h, m;
        scanf("%d %d", &h, &m);

        int total = h * 60 + m;

        printf("%d\n", (60*24) - total);
    }
}