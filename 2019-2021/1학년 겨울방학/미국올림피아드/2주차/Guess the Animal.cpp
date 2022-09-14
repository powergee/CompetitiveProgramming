#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

std::unordered_map<std::string, int> propMap;
int propNextIndex = 0;

int PropIndex(const std::string& name)
{
    auto found = propMap.find(name);
    if (found == propMap.end())
    {
        propMap[name] = propNextIndex;
        return propNextIndex++;
    }
    else
        return found->second;
}

std::unordered_map<std::string, int> nameMap;
int nameNextIndex = 0;

int NameIndex(const std::string& name)
{
    auto found = nameMap.find(name);
    if (found == nameMap.end())
    {
        nameMap[name] = nameNextIndex;
        return nameNextIndex++;
    }
    else
        return found->second;
}

std::vector<std::set<int>> animalToProp;

int CommonPropCount(int ani1, int ani2)
{
    std::vector<int> interSec(animalToProp[ani1].size() + animalToProp[ani2].size());
    auto endIt = std::set_intersection(animalToProp[ani1].begin(), animalToProp[ani1].end(),
        animalToProp[ani2].begin(), animalToProp[ani2].end(), interSec.begin());

    return endIt - interSec.begin();
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string name;
        std::cin >> name;
        int nIndex = NameIndex(name);
        animalToProp.push_back(std::set<int>());

        int count;
        std::cin >> count;
        for (int i = 0; i < count; ++i)
        {
            std::string property;
            std::cin >> property;
            int pIndex = PropIndex(property);

            animalToProp[nIndex].insert(pIndex);
        }
    }

    int result = -1;

    for (int ani1 = 0; ani1 < n; ++ani1)
        for (int ani2 = 0; ani2 < ani1; ++ani2)
            result = std::max(result, CommonPropCount(ani1, ani2));

    printf("%d", result + 1);

    return 0;
}