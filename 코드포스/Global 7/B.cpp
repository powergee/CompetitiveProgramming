#include <iostream>

int a[200000];

int main()
{
    int n, b, maxA;
    scanf("%d", &n);

    scanf("%d", a);
    maxA = a[0];
    for (int i = 1; i < n; ++i)
    {
        scanf("%d", &b);
        a[i] = maxA + b;
        
        if (b > 0)
            maxA = a[i];
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
}