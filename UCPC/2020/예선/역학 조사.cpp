#include <iostream>
#include <vector>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> groups;
    std::vector<int> infCount(m, 0);
    std::vector<bool> infected;
    std::vector<std::vector<int>> participated(n);

    for (int i = 0; i < m; ++i)
    {
        groups.emplace_back();
        int count;
        scanf("%d", &count);

        for (int j = 0; j < count; ++j)
        {
            int person;
            scanf("%d", &person);
            groups.back().push_back(person-1);
            participated[person-1].push_back(i);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int inf;
        scanf("%d", &inf);
        infected.push_back(inf == 1);
        if (inf == 1)
            for (int groupIndex : participated[i])
                ++infCount[groupIndex];
    }

    std::vector<bool> answer(n, false);
    std::vector<bool> check(n, false);

    for (int i = 0; i < n; ++i)
    {
        bool isSuspicious = true;
        for (int groupIndex : participated[i])
        {
            if (infCount[groupIndex] != (int)groups[groupIndex].size())
            {
                isSuspicious = false;
                break;
            }
        }

        if (isSuspicious)
        {
            answer[i] = true;
            for (int groupIndex : participated[i])
                for (int person : groups[groupIndex])
                    check[person] = true;
        }
    }

    bool success = true;

    for (int i = 0; i < n && success; ++i)
        if (check[i] != infected[i])
            success = false;

    if (success)
    {
        printf("YES\n");
        for (int i = 0; i < n; ++i)
            printf("%d ", answer[i] ? 1 : 0);
    }
    else
        printf("NO");

    return 0;
}