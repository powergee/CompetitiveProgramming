#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

struct SpotInfo
{
    Long Pos, Cost;
    int Index;
};

int l, n, rf, rb;
std::vector<SpotInfo> spots;
// bestSpots[i]: 인덱스 i 부터 끝까지 고려했을때, 최대의 Cost를 가지는 Spot
std::vector<SpotInfo> bestSpots;

Long CalcAnswer(int start)
{
    if (start >= bestSpots.size())
        return 0;

    SpotInfo best = bestSpots[start];
    return (best.Pos - spots[start - 1].Pos) * (rf - rb) * best.Cost + CalcAnswer(best.Index + 1);
}

int main()
{
    scanf("%d %d %d %d", &l, &n, &rf, &rb);

    spots.resize(n + 1);
    bestSpots.resize(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        Long x, c;
        scanf("%lld %lld", &x, &c);
        spots[i] = {x, c, i};
    }

    bestSpots[0] = {0, 0, -1};
    bestSpots[n] = spots[n];

    for (int i = n - 1; i > 0; --i)
    {
        if (bestSpots[i + 1].Cost <= spots[i].Cost)
            bestSpots[i] = spots[i];
        else bestSpots[i] = bestSpots[i + 1];
    }

    printf("%lld", CalcAnswer(1));

    return 0;
}