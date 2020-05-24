#include <iostream>
#include <algorithm>
 
int main()
{
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
 
    int aPos = -1, bPos = -1;
 
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%d", &a);
 
        if (a % p != 0 && aPos == -1)
            aPos = i;
    }
 
    for (int i = 0; i < m; ++i)
    {
        int b;
        scanf("%d", &b);
 
        if (b % p != 0 && bPos == -1)
            bPos = i;
    }
    
    int answer = aPos + bPos;

    if (answer > n + m - 2)
        printf("%d", std::max(aPos, bPos));
    else printf("%d", answer);
 
    return 0;
}