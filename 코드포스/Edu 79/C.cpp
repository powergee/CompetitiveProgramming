#include <iostream>

int stackArr[100000];
int listArr[100000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i)
            scanf("%d", stackArr + i);

        for (int i = 0; i < m; ++i)
            scanf("%d", listArr + i);

        
    }
}