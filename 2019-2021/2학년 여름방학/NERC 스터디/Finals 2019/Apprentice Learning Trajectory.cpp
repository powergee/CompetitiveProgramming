#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

struct Work
{
    Long s, e, t;

    bool operator<(const Work& w) const
    {
        if (s == w.s)
            return t < w.t;
        return s < w.s;
    }
};

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<Work> works;
    for (int i = 0; i < n; ++i)
    {
        Long s, e, t;
        scanf("%lld %lld %lld", &s, &e, &t);
        works.emplace_back(s, e, t);
    }

    std::sort(works.begin(), works.end());
    

    return 0;
}