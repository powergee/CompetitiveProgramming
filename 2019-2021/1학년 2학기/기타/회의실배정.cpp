#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::pair<int, int>> v;

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        v.push_back({end, start});
    }

    std::sort(v.begin(), v.end());

    int maxEnd = v[0].first;
    int count = 1;
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i].second >= maxEnd)
        {
            maxEnd = v[i].first;
            ++count;
        }
    }

    printf("%d", count);

    return 0;
}