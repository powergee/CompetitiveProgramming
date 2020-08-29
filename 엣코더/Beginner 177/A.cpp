#include <iostream>

int main()
{
    int d, t, s;
    scanf("%d %d %d", &d, &t, &s);
    printf("%s", t*s >= d ? "Yes" : "No");
    return 0;
}