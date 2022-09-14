#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <climits>

std::map<int, std::vector<std::pair<int, int>>> queries;
int diff[100000];
int answer[100000];
int n, q;

void fillAnswer(int s, const std::vector<std::pair<int, int>>& ks)
{
    int currK = 1;
    int vIndex = 0;
    int left, right;
    if (s == 1)
    {
        left = -1;
        right = 0;
    }
    else if (s == n)
    {
        left = n - 2;
        right = -1;
    }
    else
    {
        left = s - 2;
        right = s - 1;
    }

    while (left != -1 || right != -1)
    {
        while (vIndex < (int)ks.size() && ks[vIndex].first == currK)
        {
            answer[ks[vIndex].second] = s;
            ++vIndex;
        }

        if (vIndex == (int)ks.size())
            break;

        bool openLeft = false;
        bool openRight = false;
        if (left == -1)
            openRight = true;
        else if (right == -1)
            openLeft = true;
        else if (diff[left] < diff[right])
            openLeft = true;
        else if (diff[left] > diff[right])
            openRight = true;

        if (openLeft)
        {
            s = left + 1;
            ++currK;
            --left;
        }
        else
        {
            s = right + 2;
            ++currK;
            ++right;
            if (right == n-1)
                right = -1;
        }
    }
    while (vIndex < (int)ks.size() && ks[vIndex].first == currK)
    {
        answer[ks[vIndex].second] = s;
        ++vIndex;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t)
    {
        scanf("%d %d", &n, &q);
        queries.clear();

        for (int i = 0; i < n - 1; ++i)
            scanf("%d", diff + i);

        for (int i = 0; i < q; ++i)
        {
            int s, k;
            scanf("%d %d", &s, &k);
            if (queries.find(s) == queries.end())
                queries[s] = std::vector<std::pair<int, int>>();
            queries[s].emplace_back(k, i);
        }

        for (auto& qPair : queries)
        {
            int s = qPair.first;
            std::sort(qPair.second.begin(), qPair.second.end());
            fillAnswer(s, qPair.second);
        }

        printf("Case #%d: ", t);
        for (int i = 0; i < q; ++i)
            printf("%d ", answer[i]);
        printf("\n");
    }

    return 0;
}