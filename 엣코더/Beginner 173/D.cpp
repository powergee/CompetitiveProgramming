#include <iostream>
#include <algorithm>
#include <queue>

typedef long long Long;
typedef std::pair<int, int> interval;

int fri[200000];

struct comparator
{
    bool operator()(const interval i1, const interval i2) const
    {
        return std::min(fri[i1.first], fri[i1.second]) < std::min(fri[i2.first], fri[i2.second]);
    }
};

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", fri + i);

    std::sort(fri, fri + n, std::greater<int>());
    std::priority_queue<interval, std::vector<interval>, comparator> intQ;
    intQ.push({0, 0});
    Long result = 0;

    for (int i = 1; i < n; ++i)
    {
        interval now = intQ.top();
        intQ.pop();

        result += std::min(fri[now.first], fri[now.second]);
        intQ.push({now.first, i});
        intQ.push({now.second, i});
    }

    std::cout << result;

    return 0;
}