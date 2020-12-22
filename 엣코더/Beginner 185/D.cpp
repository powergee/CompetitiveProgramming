#include <iostream>
#include <vector>
#include <algorithm>

int paint(int segWidth, int k)
{
    if (segWidth == 0)
        return 0;
    return (segWidth / k) + (segWidth % k > 0 ? 1 : 0);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    if (m == 0)
    {
        printf("1");
    }
    else
    {
        std::vector<int> pos;

        for (int i = 0; i < m; ++i)
        {
            int p;
            scanf("%d", &p);
            pos.push_back(p);
        }
        
        std::sort(pos.begin(), pos.end());

        int k = (pos[0] == 1 ? INT32_MAX : pos[0] - 1);
        for (int i = 0; i < (int)pos.size() - 1; ++i)
        {
            int dist = pos[i+1] - pos[i] - 1;
            if (dist >= 1)
                k = std::min(k, dist);
        }
        if (pos.back() != n)
            k = std::min(k, n - pos.back());
        
        // printf("%d\n", k);

        int count = paint(pos[0] - 1, k);
        // printf("%d\n", count);
        for (int i = 0; i < (int)pos.size() - 1; ++i)
        {
            int dist = pos[i+1] - pos[i] - 1;
            count += paint(dist, k);
            // printf("%d\n", count);
        }
        count += paint(n - pos.back(), k);

        printf("%d", count);
    }
    return 0;
}