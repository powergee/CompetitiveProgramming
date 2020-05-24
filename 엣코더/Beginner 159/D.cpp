#include <iostream>
#include <map>
#include <vector>

typedef long long Long;

std::map<int, int> count;
void AddNum(int num)
{
    auto found = count.find(num);
    if (found == count.end())
        count[num] = 1;
    else ++found->second;
}

int arr[200001];
Long dp[200001];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", arr + i);
        AddNum(arr[i]);
    }

    std::vector<Long> cases;
    Long left = 0, right = 0;
    for (auto p : count)
    {
        cases.push_back((Long)p.second * (p.second - 1) / 2);
        right += cases.back();
    }

    int i = 0;
    for (auto p : count)
    {
        right -= cases[i];
        if (i > 0)
            left += cases[i-1];
        
        dp[p.first] = left + right + (((Long)p.second - 1)*(p.second - 2) / 2);
        ++i;
    }

    for (i = 0; i < n; ++i)
        printf("%lld\n", dp[arr[i]]);

    return 0;
}