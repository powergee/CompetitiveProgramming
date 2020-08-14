#include <iostream>
#include <algorithm>

typedef long long Long;

struct Work
{
    Long s, e, t;

    bool operator<(const Work& other) const
    {
        if (s == other.s)
            return e < other.e;
        return s < other.s;
    }
};

Work works[200000];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%lld %lld %lld", &works[i].s, &works[i].e, &works[i].t);
    std::sort(works, works+n);

    

    return 0;
}