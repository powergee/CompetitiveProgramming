#include <iostream>
 
int main()
{
    int T;
    scanf("%d", &T);
 
    while (T--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
 
        printf("%d\n", a + b - (a & b) * 2);
    }
 
    return 0;
}