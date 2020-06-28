#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

struct Item
{
    int price = 0, size = 0, num = 0;

    bool operator<(const Item& other) const
    {
        if (price != other.price)
            return price < other.price;

        return size < other.size;
    }
};

struct ComparePrice
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.size < i2.size;
    }
};

int n;
Item items[2][500000];
std::vector<std::multiset<Item, ComparePrice>> groups[2];
std::vector<int> answer[2];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < n; ++j)
            scanf("%d", &items[i][j].price);
        for (int j = 0; j < n; ++j)
            scanf("%d", &items[i][j].size);
        for (int j = 0; j < n; ++j)
            items[i][j].num = j + 1;

        std::sort(items[i], items[i] + n);
        for (int j = 0; j < n; ++j)
        {
            if (groups[i].empty() || items[i][j].price != groups[i].back().begin()->price)
                groups[i].emplace_back();

            groups[i].back().insert(items[i][j]);
        }
    }

    int backIndex = 0, frontIndex = 0;
    bool possible = true;
    while (backIndex < (int)groups[0].size() && frontIndex < (int)groups[1].size() && possible)
    {
        auto& backGroup = groups[0][backIndex];
        auto& frontGroup = groups[1][frontIndex];

        if (backGroup.size() < frontGroup.size())
        {
            while (!backGroup.empty())
            {
                auto bigger = backGroup.begin();
                auto found = frontGroup.lower_bound(*bigger);

                if (found == frontGroup.begin())
                {
                    possible = false;
                    break;
                }

                --found;
                answer[0].push_back(bigger->num);
                answer[1].push_back(found->num);
                frontGroup.erase(found);
                backGroup.erase(bigger);
            }
        }
        else
        {
            while (!frontGroup.empty())
            {
                auto smaller = frontGroup.begin();
                auto found = backGroup.upper_bound(*smaller);

                if (found == backGroup.end())
                {
                    possible = false;
                    break;
                }

                answer[0].push_back(found->num);
                answer[1].push_back(smaller->num);
                frontGroup.erase(smaller);
                backGroup.erase(found);
            }
        }

        if (backGroup.empty())
            ++backIndex;
        if (frontGroup.empty())
            ++frontIndex;
    }

    if (possible)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int val : answer[i])
                printf("%d ", val);
            printf("\n");
        }
    }
    else printf("impossible");

    return 0;
}