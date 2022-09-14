#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <vector>

class Log
{
public:
    int day, diff;
    int id;

    bool operator < (const Log& log) const
    {
        return day < log.day;
    }
};

std::unordered_map<std::string, int> map;
int nextIndex = 0;

int GetIndex(std::string name)
{
    auto found = map.find(name);
    if (found == map.end())
    {
        map[name] = nextIndex;
        return nextIndex++;
    }
    else
        return found->second;
}

void GetSet(std::unordered_set<int>& result, const std::vector<int>& prod, int value)
{
    result.clear();

    for (int i = 0; i < prod.size(); ++i)
    {
        if (value == prod[i])
            result.insert(i);
    }
}

std::vector<Log> logs;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        Log log;
        std::string name;

        std::cin >> log.day >> name >> log.diff;
        log.id = GetIndex(name);

        logs.push_back(log);
    }

    std::sort(logs.begin(), logs.end());

    std::vector<int> prod(map.size());
    std::fill(prod.begin(), prod.end(), 7);

    int count = 0;
    std::unordered_set<int> maxSet;
    GetSet(maxSet, prod, 7);

    for (Log& log : logs)
    {
        prod[log.id] += log.diff;

        std::unordered_set<int> nextSet;
        GetSet(nextSet, prod, *(std::max_element(prod.begin(), prod.end())));

        if (maxSet != nextSet)
        {
            maxSet = nextSet;
            ++count;
        }
    }

    std::cout << count;

    return 0;
}
