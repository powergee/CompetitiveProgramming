#include <iostream>
#include <set>
#include <vector>

std::vector<int> buckets[2];
std::set<int> results;

void Copy(int except, const std::vector<int>& from, std::vector<int>& to)
{
    for (int i = 0; i < from.size(); ++i)
        if (except != i)
            to.push_back(from[i]);
}


void Process(int days, int amount, const std::vector<int>& from, const std::vector<int>& to)
{
    if (days == 4)
    {
        results.insert(amount);
        return;
    }

    for (int i = 0; i < from.size(); ++i)
    {
        std::vector<int> newFrom;
        Copy(i, from, newFrom);
        std::vector<int> newTo(to.begin(), to.end());
        newTo.push_back(from[i]);

        Process(days + 1, amount + (days % 2 ? 1 : -1) * from[i], newTo, newFrom);
    }
}

int main()
{
    buckets[0].resize(10);
    buckets[1].resize(10);
    for (int barn = 0; barn < 2; ++barn)
        for (int i = 0; i < 10; ++i)
            scanf("%d", &buckets[barn][i]);
    
    Process(0, 1000, buckets[0], buckets[1]);
    printf("%d", results.size());
}