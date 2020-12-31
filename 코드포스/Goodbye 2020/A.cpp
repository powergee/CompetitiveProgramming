#include <iostream>
#include <set>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, x[50];
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", x+i);
        
        std::set<int> dist;
        for (int i = 0; i < n; ++i)
            for (int j = i+1; j < n; ++j)
                dist.insert(x[j] - x[i]);
        
        printf("%d\n", (int)dist.size());
    }

    return 0;
}