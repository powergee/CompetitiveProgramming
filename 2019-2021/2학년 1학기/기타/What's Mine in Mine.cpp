#include <iostream>
#include <algorithm>
#include <tuple>

int m, n;
int price[101];
std::tuple<int, int, int> mineral[10000];
int dp[10000];

int GetMaxIncome(int start)
{
    if (start >= n)
        return 0;

    int& result = dp[start];
    if (result != -1)
        return result;
    
    int s, e, t;
    std::tie(s, e, t) = mineral[start];
    int income = (e - s) * price[t];
    
    int next = start;
    while (next < n && std::get<0>(mineral[next]) < e)
        ++next;
    
    return result = std::max(income + GetMaxIncome(next), GetMaxIncome(start + 1));
}

int main()
{
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i)
        scanf("%d", price + i);

    for (int i = 0; i < n; ++i)
    {
        int s, e, t;
        scanf("%d %d %d", &s, &e, &t);
        mineral[i] = std::make_tuple(s, e, t);
    }

    std::sort(mineral, mineral + n);
    std::fill(dp, dp + n, -1);
    printf("%d", GetMaxIncome(0));

    return 0;
}