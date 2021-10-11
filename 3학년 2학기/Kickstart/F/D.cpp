#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

typedef long long Long;

struct VerInfo {
    Long l, r, a;

    VerInfo() {}
    VerInfo(Long l, Long r, Long a) {
        this->l = l;
        this->r = r;
        this->a = a;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);;

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        Long n, m, k;
        std::cin >> n >> m >> k;

        std::vector<Long> dp((1<<n), -1);
        std::vector<VerInfo> verInfo;
        std::vector<std::vector<int>> graph(n);
        
        for (int i = 0; i < n; ++i) {
            int l, r, a;
            std::cin >> l >> r >> a;
            verInfo.emplace_back(l, r, a);
        }

        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        std::function<Long(int)> countCases;
        countCases = [&](int state) -> Long {
            if (dp[state] != -1) {
                return dp[state];
            }
            Long magic = 0;
            for (int i = 0; i < n; ++i) {
                if (state & (1<<i)) {
                    magic += verInfo[i].a;
                }
            }
            if (magic == k) {
                return dp[state] = 1;
            }
            dp[state] = 0;
            for (int i = 0; i < n; ++i) {
                if (verInfo[i].l <= magic && magic <= verInfo[i].r && (state & (1<<i)) == 0) {
                    bool ready = false;
                    for (int j : graph[i]) {
                        if (state & (1<<j)) {
                            ready = true;
                            break;
                        }
                    }
                    if (ready) {
                        dp[state] += countCases(state | (1<<i));
                    }
                }
            }
            return dp[state];
        };

        Long answer = 0;
        for (int i = 0; i < n; ++i) {
            answer += countCases(1<<i);
        }
        printf("%lld\n", answer);
    }

    return 0;
}