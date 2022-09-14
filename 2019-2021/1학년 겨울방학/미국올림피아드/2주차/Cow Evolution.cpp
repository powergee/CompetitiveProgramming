#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <list>

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

int main()
{


    return 0;
}