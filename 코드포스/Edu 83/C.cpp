#include <iostream>
#include <vector>
#include <set>

typedef long long Long;

bool CanDivide(Long val, int k, std::set<Long>& used)
{
    Long first = k;

    while (first < val)
        first *= k;

    while (first > 0 && val != 0)
    {
        if (val >= first && used.find(first) == used.end())
        {
            val -= first;
            used.insert(first);
        }

        first /= k;
    }

    return val == 0;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<Long> arr;
        std::set<Long> used;

        for (int i = 0; i < n; ++i)
        {
            Long input;
            scanf("%lld", &input);
            if (input != 0)
                arr.push_back(input);
        }

        bool yes = true;
        for (int i = 0; i < (int)arr.size() && yes; ++i)
            yes = CanDivide(arr[i], k, used);

        if (yes) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}