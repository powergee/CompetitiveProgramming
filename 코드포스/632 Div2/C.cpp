#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long Long;
Long a[200001];
Long sum[200001];
// value, count
std::map<Long, std::vector<int>*> countMap;

int main()
{
    Long n;
    scanf("%lld", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i-1] + a[i];
    
    for (int i = 0; i <= n; ++i)
    {
        auto found = countMap.find(sum[i]);
        if (found == countMap.end())
        {
            std::vector<int>* newVec = new std::vector<int>;
            newVec->push_back(i);
            countMap[sum[i]] = newVec;
        }
        else found->second->push_back(i);
    }

    Long good = 0;
    std::vector<int> allPos;
    for (auto p : countMap)
        if (p.second->size() >= 2)
            for (int pos : *p.second)
                allPos.push_back(pos);
    
    std::sort(allPos.begin(), allPos.end());
    good += allPos[0] - 

    return 0;
}