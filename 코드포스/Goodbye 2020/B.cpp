#include <iostream>
#include <set>
#include <map>
#include <vector>

int main()
{
    // freopen("out", "w", stdout);
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        std::set<int> diversity;
        std::map<int, int> count;
        std::vector<int> prev;

        for (int i = 0; i < n; ++i)
        {
            int val;
            scanf("%d", &val);
            count[val] += 1;
            diversity.insert(val);
        }

        for (int v : diversity)
            prev.push_back(v);

        for (int v : prev)
        {
            if (count[v] > 1)
            {
                diversity.insert(v+1);
                count[v+1] += 1;
            }
        }
        
        printf("%d\n", (int)diversity.size());
    }

    return 0;
}