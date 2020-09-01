#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long Long;
Long dp[30][30];

Long countCombinations(int n, int k)
{
    if (n < k)
        return 0;
    if (n == 0 || k == 0)
        return 1;
    
    if (dp[n][k] != -1)
        return dp[n][k];
    
    return dp[n][k] = countCombinations(n-1, k-1) + countCombinations(n-1, k);
}

Long countCases(int remCount, std::map<int, int> &count)
{
    int prevSum = 0;
    Long result = 1;
    for (auto it = std::prev(count.end());; --it)
    {
        if (it->first == 0)
            result *= countCombinations(remCount - prevSum, it->second);
        else
            result *= countCombinations(remCount + 1 - it->first - prevSum, it->second);
        prevSum += it->second;

        if (it == count.begin())
            break;
    }

    return result;
}

int main()
{
    std::fill(&dp[0][0], &dp[0][0]+sizeof(dp)/sizeof(Long), -1LL);
    int T;
    scanf("%d", &T);

    while (T--)
    {
        Long k;
        int div = 2;
        int remCount = 0;
        scanf("%lld", &k);
        std::map<int, int> count;

        do
        {
            count[k % div] += 1;
            k /= div++;
            ++remCount;
        } while (k > 0);
        
        Long result = countCases(remCount, count);
        if (count.find(0) != count.end())
        {
            --count[0];
            result -= countCases(remCount-1, count);
        }

        printf("%lld\n", result-1);
    }

    return 0;
}