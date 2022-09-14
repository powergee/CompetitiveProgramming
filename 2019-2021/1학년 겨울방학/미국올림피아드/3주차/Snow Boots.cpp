#include <iostream>
#include <unordered_set>
#include <functional>
#include <algorithm>

struct Boots
{
    int Depth;
    int Step;
};

int depth[250];
Boots pairs[250];
std::unordered_set<int> footPrint[250];
int n, b;

void AddFootPrint(int pairIndex, int pos)
{
    while (pos < n && depth[pos] <= pairs[pairIndex].Depth)
    {
        footPrint[pos].insert(pairIndex);
        //printf("%d was added on footPrint[%d]\n", pairIndex, pos);

        bool moved = false;
        for (int dist = 1; dist <= pairs[pairIndex].Step; ++dist)
        {
            if (dist + pos < n && depth[dist + pos] <= pairs[pairIndex].Depth)
            {
                moved = true;
                pos += dist;
                break;
            }
        }

        if (!moved)
            break;
    }
}

void TryToGo(int pairIndex, int start)
{
    if (pairIndex >= b)
        return;

    int nextStart = -1;
    for (int pos = start; pos < n; ++pos)
    {
        if (!footPrint[pos].empty())
        {
            if (nextStart == -1)
                nextStart = pos;
            AddFootPrint(pairIndex, pos);
        }
    }

    if (nextStart != -1)
        TryToGo(pairIndex + 1, nextStart);
}

int main()
{
    scanf("%d %d", &n, &b);

    for (int i = 0; i < n; ++i)
        scanf("%d", depth + i);

    for (int i = 0; i < b; ++i)
        scanf("%d %d", &pairs[i].Depth, &pairs[i].Step);

    AddFootPrint(0, 0);
    TryToGo(1, 0);

    printf("%d", *std::min_element(footPrint[n - 1].begin(), footPrint[n - 1].end()));
}