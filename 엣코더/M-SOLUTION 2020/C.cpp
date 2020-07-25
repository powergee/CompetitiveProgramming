#include <iostream>

int grade[200000];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", grade+i);
    
    for (int i = k; i < n; ++i)
    {
        if (grade[i-k] < grade[i])
            printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}