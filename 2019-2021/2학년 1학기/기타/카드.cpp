#include <iostream>
#include <map>

typedef long long Long;

std::map<Long, int> count;
void AddNum(Long num)
{
    auto found = count.find(num);
    if (found == count.end())
        count.insert({ num, 1 });
    else ++found->second;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        Long num;
        scanf("%lld", &num);
        AddNum(num);
    }

    std::pair<Long, int> max(0, -1);
    for (auto p : count)
        if (max.second < p.second)
            max = p;

    std::cout << max.first;

    return 0;
}