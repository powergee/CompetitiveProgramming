#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

typedef int CowIndex;

struct Measurement
{
    int Day;
    int Diff;
    CowIndex Cow;

    bool operator<(const Measurement& other) const
    {
        return Day < other.Day;
    }
};

std::vector<int> milkProd;
std::vector<Measurement> meaVec;

std::unordered_map<int, CowIndex> idToIndex;

int GetIndex(int id)
{
    auto found = idToIndex.find(id);

    if (found == idToIndex.end())
    {
        milkProd.push_back(0);

        CowIndex newIndex = idToIndex.size();
        idToIndex[id] = newIndex;
        return newIndex;
    }
    else return found->second;
}

struct CowIndexCompare
{
    bool operator()(const CowIndex& c1, const CowIndex& c2) const
    {
        if (milkProd[c1] == milkProd[c2])
            return c1 < c2;
        return milkProd[c1] > milkProd[c2];
    }
};

int main()
{
    int n, g;
    scanf("%d %d", &n, &g);

    std::set<CowIndex, CowIndexCompare> cowRanking;
    for (int i = 0; i < n; ++i)
    {
        int day, cowId, diff;
        scanf("%d %d %d", &day, &cowId, &diff);

        CowIndex cIndex = GetIndex(cowId);
        cowRanking.insert(cIndex);
        meaVec.push_back({ day, diff, cIndex });
    }

    CowIndex cIndex = GetIndex(-1);
    cowRanking.insert(cIndex);

    std::sort(meaVec.begin(), meaVec.end());

    int count = 0;
    for (Measurement& m : meaVec)
    {
        auto changerIt = cowRanking.find(m.Cow);
        int& prodChanger = milkProd[m.Cow];
        int prod1st = milkProd[*cowRanking.begin()];
        int prod2nd = milkProd[*(std::next(cowRanking.begin()))];

        if (prod1st == prodChanger) // 바뀌는 소가 전광판에 표시되고 있는 소들 중 하나임.
        {
            if (prod1st == prod2nd) // 공동 1등일 때, 증감 여부와 관계없이 화면에 표시되는 집단은 바뀜.
            {
                ++count;
            }
            else // 유일한 1등일 때, diff > 0 이면 변화가 없으나 diff < 0 일 때는 상황에 달림.
            {
                if (prod1st + m.Diff <= prod2nd)
                    ++count;
            }
        }
        else
        {
            if (prod1st <= prodChanger + m.Diff)
                ++count;
        }

        cowRanking.erase(changerIt);
        prodChanger += m.Diff;
        cowRanking.insert(m.Cow);
    }

    printf("%d", count);

    return 0;
}