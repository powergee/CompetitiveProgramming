#include <iostream>
#include <set>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        std::set<int> appeared[2];
        for (int i = 0; i < n; ++i)
        {
            int val;
            scanf("%d", &val);
            appeared[0].insert(val);
        }
        for (int i = 0; i < m; ++i)
        {
            int val;
            scanf("%d", &val);
            appeared[1].insert(val);
        }

        

        bool found = false;
        for (auto ele : appeared[0])
        {
            if (appeared[1].find(ele) != appeared[1].end())
            {
                printf("YES\n");
                printf("1 %d\n", ele);
                found = true;
                break;
            }
        }

        if (!found)
            printf("NO\n");
    }

    return 0;
}