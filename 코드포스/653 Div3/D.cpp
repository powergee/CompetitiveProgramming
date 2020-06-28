#include <iostream>
#include <map>
#include <algorithm>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        std::map<int, int> count;
        int n, k;
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; ++i)
        {
            int val;
            scanf("%d", &val);
            val %= k;
            count[val] += 1;
        }

        long long answer = 0;
        for (auto p : count)
        {
            if (p.first == 0)
                continue;
            answer = std::max(answer, 1 + k * ((long long)p.second - 1) + (k - p.first));
        }

        printf("%lld\n", answer);
    }

    return 0;
}