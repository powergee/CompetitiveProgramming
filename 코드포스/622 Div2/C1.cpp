#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

typedef long long Long;

Long m[1000];
std::deque<Long> ds[1000];
int n;

Long Calc(int top)
{
    std::deque<Long>& d = ds[top];
    Long sum = m[top];
    d.push_front(m[top]);

    for (int i = top - 1; i >= 0; --i)
    {
        Long add = std::min(d.front(), m[i]);
        d.push_front(add);
        sum += add;
    }

    for (int i = top + 1; i < n; ++i)
    {
        Long add = std::min(d.back(), m[i]);
        d.push_back(add);
        sum += add;
    }

    return sum;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%lld", m + i);

    std::vector<Long> vec;

    for (int i = 0; i < n; ++i)
        vec.push_back(Calc(i));

    std::deque<Long>& answer = ds[std::max_element(vec.begin(), vec.end()) - vec.begin()];

    while (!answer.empty())
    {
        printf("%lld ", answer.front());
        answer.pop_front();
    }

    return 0;
}