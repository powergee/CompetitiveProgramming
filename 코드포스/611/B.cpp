#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, k;
        scanf("%d %d", &n, &k);

        int given = (n / k) * k;
        int remain = n % k;
        
        given += remain > (k / 2) ? (k/2) : remain;

        printf("%d\n", given);
    }
}