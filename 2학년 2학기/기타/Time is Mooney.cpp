#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

int n, m, c;

struct TripResult
{
    bool arrived;
    int earned, elapsed;

    TripResult()
    {
        arrived = false;
        earned = elapsed = 0;
    }

    TripResult(bool arrived, int earned, int elapsed)
    {
        this->arrived = arrived;
        this->earned = earned;
        this->elapsed = elapsed;
    }

    int calcMooney() const
    {
        return earned - c * std::pow(elapsed, 2);
    }

    bool operator<(const TripResult &t) const
    {
        return calcMooney() < t.calcMooney();
    }

    bool operator!=(const TripResult &t) const
    {
        return earned == t.earned && elapsed == t.elapsed;
    }
};

const TripResult DEFAULT = TripResult(false, -1, -1);
const TripResult NO_VALID_ANSWERS = TripResult(false, 0, 0);

int income[1000];
std::vector<int> graph[1000];
TripResult dp[1000][1000];

TripResult startTrip(int start, int time)
{
    if (time >= 1000)
        return NO_VALID_ANSWERS;

    TripResult &result = dp[start][time];
    if (result != DEFAULT)
        return result;

    result = NO_VALID_ANSWERS;
    int validNext = -1;
    for (int next : graph[start])
    {
        TripResult subResult = startTrip(next, time + 1);
        if (subResult.arrived && result < subResult)
        {
            validNext = next;
            result = subResult;
        }
    }

    if (start == 1)
        return result = TripResult(true, result.earned, result.elapsed);
    else if (validNext == -1)
        return result = NO_VALID_ANSWERS;
    else
        return result = TripResult(true, result.earned + income[validNext], result.elapsed + time);
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < n; ++i)
        scanf("%d", income + i);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u - 1].push_back(v - 1);
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(TripResult), DEFAULT);
    printf("%d", startTrip(1, 0).calcMooney());

    return 0;
}