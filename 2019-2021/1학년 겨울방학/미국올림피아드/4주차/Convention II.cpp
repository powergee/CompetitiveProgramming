#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
#define ARRIVE 0
#define EAT 2
#define SENIORITY 1
typedef std::tuple<int, int, int> CowInfo;

struct CowCompare
{
public:
    bool operator()(const CowInfo& c1, const CowInfo& c2)
    {
        return std::get<SENIORITY>(c1) > std::get<SENIORITY>(c2);
    }
};

int n;
std::priority_queue<CowInfo, std::vector<CowInfo>, CowCompare> waitingQueue;
std::set<CowInfo> infoSet;

bool GetNext(CowInfo& infoResult)
{
    if (waitingQueue.empty())
    {
        if (infoSet.empty())
            return false;

        infoResult = *infoSet.begin();
        return true;
    }
    else
    {
        infoResult = waitingQueue.top();
        waitingQueue.pop();
        return true;
    }
}

void UpdateContainer(const CowInfo& usedInfo, int currTime)
{
    infoSet.erase(usedInfo);

    std::vector<std::set<CowInfo>::iterator> pushed;
    for (auto it = infoSet.begin(); it != infoSet.end(); ++it)
    {
        if (std::get<ARRIVE>(*it) > currTime)
            break;

        waitingQueue.push(*it);
        pushed.push_back(it);
    }

    for (auto it : pushed)
        infoSet.erase(it);
}

int main()
{
    scanf("%d", &n);

    for (int s = 0; s < n; ++s)
    {
        int arr, eat;
        scanf("%d %d", &arr, &eat);

        infoSet.insert(std::make_tuple(arr, s, eat));
    }

    int currTime = 0;
    CowInfo currCow;
    int maxWaiting = -1;
    while (GetNext(currCow))
    {
        int arr, eat, sen;
        std::tie(arr, sen, eat) = currCow;

        currTime = std::max(currTime, arr);
        maxWaiting = std::max(currTime - arr, maxWaiting);
        currTime += eat;

        UpdateContainer(currCow, currTime);
    }

    printf("%d", maxWaiting);

    return 0;
}