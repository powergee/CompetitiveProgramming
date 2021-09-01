#include <iostream>
#include <algorithm>
#define MOD 998244353

typedef long long Long;

struct Portal {
    int from, to;
    bool active;

    Portal() {}
    Portal(int from, int to, bool active) {
        this->from = from;
        this->to = to;
        this->active = active;
    }
} portals[200000];

Long dp[200000];
Long sumDP[200000];
int n;

Portal* findNearest(int start) {
    return std::lower_bound(portals, portals+n, Portal(start, -1, 0), [](const Portal& p1, const Portal& p2) -> bool {
        return p1.from < p2.from;
    });
}

Long calcTimeToReach(int endIdx);
Long calcReturningTime(int pIdx);

Long calcTimeToReach(int endIdx) {
    if (sumDP[endIdx] != -1) {
        return sumDP[endIdx];
    }
    if (endIdx == 0) {
        return sumDP[endIdx] = portals[endIdx].from;
    }
    return sumDP[endIdx] = (calcTimeToReach(endIdx-1) + calcReturningTime(endIdx-1) + 
                            portals[endIdx].from - portals[endIdx-1].from) % MOD;    
}

Long calcReturningTime(int pIdx) {
    if (dp[pIdx] != -1LL) {
        return dp[pIdx];
    }

    auto nearest = findNearest(portals[pIdx].to);
    if (nearest == portals+pIdx) {
        return dp[pIdx] = (portals[pIdx].from - portals[pIdx].to) % MOD;
    }

    dp[pIdx] = (nearest->from - portals[pIdx].to) + (calcTimeToReach(pIdx) - calcTimeToReach(nearest-portals));
    while (dp[pIdx] < 0) {
        dp[pIdx] += MOD;
    }
    dp[pIdx] %= MOD;
    return dp[pIdx];
}

int main() {
    scanf("%d", &n);
    std::fill(dp, dp+n, -1LL);
    std::fill(sumDP, sumDP+n, -1LL);

    for (int i = 0; i < n; ++i) {
        int x, y, s;
        scanf("%d %d %d", &x, &y, &s);
        portals[i] = { x, y, (s == 1) };
    }

    Long answer = 0;
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (portals[i].active) {
            answer += portals[i].from - pos + calcReturningTime(i);
            answer %= MOD;
            pos = portals[i].from;
        }
    }

    answer += portals[n-1].from+1 - pos;
    answer %= MOD;

    printf("%lld", answer);

    return 0;
}