#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
std::vector<int> results[100];
std::vector<int>* sorted[100];
std::vector<int> canceled[100];
int sum[100];

bool compareResults(const std::vector<int>* r1, const std::vector<int>* r2, int cand)
{
    return (*r1)[cand] - r1->back() < (*r2)[cand] - r2->back(); 
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int count;
            scanf("%d", &count);
            results[i].push_back(count);
            sum[j] += count;
        }
        sorted[i] = results + i;
    }

    int minCount = 1e9;
    int selected;
    for (int i = 0; i < n-1; ++i)
    {
        std::sort(sorted, sorted + m, 
            [&](auto r1, auto r2) -> bool { return compareResults(r1, r2, i); });
        
        int cand = sum[i];
        int op = sum[n-1];

        for (int j = 0; cand < op; ++j)
        {
            cand -= (*sorted[j])[i];
            op -= (*sorted[j])[n-1];
            canceled[i].push_back(sorted[j] - results + 1);
        }

        if (minCount > (int)canceled[i].size())
        {
            minCount = (int)canceled[i].size();
            selected = i;
        }
    }

    printf("%d\n", minCount);
    for (int c : canceled[selected])
        printf("%d ", c);

    return 0;
}