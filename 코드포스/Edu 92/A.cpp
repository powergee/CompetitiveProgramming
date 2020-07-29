#include <iostream>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int l, r;
        scanf("%d %d", &l, &r);

        if (r < 2*l)
            printf("-1 -1\n");
        else printf("%d %d\n", l, 2*l);        
    }

    return 0;
}