#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct HierInfo
{
    int CowNum = -1;
    int Pos = -1;
};

std::vector<int> order;
std::vector<HierInfo> hier;

void FillOrder(int oLeft, int oRight, int hLeft, int hRight)
{
    if (oRight < oLeft || hRight < hLeft || oLeft < 0 || hLeft < 0)
        return;

    for (int i = hLeft; i <= hRight; ++i)
    {
        if (hier[i].Pos != -1)
        {
            FillOrder(oLeft, hier[i].Pos - 1, hLeft, i - 1);
            FillOrder(hier[i].Pos + 1, oRight, i + 1, hRight);
            return;
        }
    }

    bool foundOne = false;
    for (int i = hLeft; i <= hRight; ++i)
    {
        if (hier[i].CowNum == 1)
        {
            foundOne = true;
            break;
        }
    }
    
    if (foundOne)
    {
        for (int hierPos = hLeft, i = oLeft; i <= oRight; ++i)
        {
            if (order[i] == -1)
            {
                order[i] = hier[hierPos++].CowNum;
                if (hierPos == hRight + 1)
                    break;
            }
        }
    }
    else
    {
        for (int hierPos = hRight, i = oRight; i >= oLeft; --i)
        {
            if (order[i] == -1)
            {
                order[i] = hier[hierPos--].CowNum;
                if (hierPos == hLeft - 1)
                    break;
            }
        }
    }
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    order.resize(n + 1);
    hier.resize(m);
    std::fill(order.begin(), order.end(), -1);

    for (int i = 0; i < m; ++i)
        scanf("%d", &hier[i].CowNum);

    for (int i = 0; i < k; ++i)
    {
        int c, p;
        scanf("%d %d", &c, &p);

        order[p] = c;
    }

    for (int h = 0; h < m; ++h)
    {
        for (int o = 1; o <= n; ++o)
        {
            if (order[o] == hier[h].CowNum)
            {
                hier[h].Pos = o;
                break;
            }
        }
    }

    FillOrder(1, n, 0, m - 1);

    for (int i = 1; i <= n; ++i)
    {
        if (order[i] == 1)
        {
            printf("%d", i);
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (order[i] == -1)
        {
            printf("%d", i);
            return 0;
        }
    }

    return 0;
}