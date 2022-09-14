#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

Long temp[100001];
Long value[100001];
int n, d;
Long answer;

inline Long Taste(Long i, Long j)
{
    return (j - i) * temp[j] + value[i];
}

void FindAnswer(int s, int e, int l, int r)
{
    if (s > e)
        return;

    int m = (s + e) >> 1;
    int k = std::max(1, m - d);

    for (int i = k; i <= std::min(m, r); ++i)
    {
        if (Taste(k, m) < Taste(i, m))
            k = i;
    }

    answer = std::max(answer, Taste(k, m));
    FindAnswer(s, m - 1, l, k);
    FindAnswer(m + 1, e, k, r);
}

int main()
{
    scanf("%d %d", &n, &d);

    for (int i = 1; i <= n; ++i)
        scanf("%lld", temp + i);

    for (int i = 1; i <= n; ++i)
        scanf("%lld", value + i);

    FindAnswer(1, n, 1, n);
    printf("%lld", answer);

    return 0;
}