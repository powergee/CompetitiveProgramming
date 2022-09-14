#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

struct Component {
    int x, y, sm, pm, sv, pv;
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Component> comps;
    for (int i = 0; i < n; ++i) {
        int x, y, sm, pm, sv, pv;
        scanf("%d %d %d %d %d %d", &x, &y, &sm, &pm, &sv, &pv);
        comps.push_back({ x, y, sm, pm, sv, pv });
    }

    auto ceilDiv = [](int n, int d) -> int {
        if (n <= 0) {
            return 0;
        }
        return n / d + (n % d ? 1 : 0);
    };

    auto buyOptimally = [&](Component& comp, int count) -> int {
        int bound = ceilDiv(count, comp.sm);
        int result = INT32_MAX;
        for (int i = 0; i <= bound; ++i) {
            int j = ceilDiv((count - i*comp.sm), comp.sv);
            result = std::min(result, i*comp.pm + j*comp.pv);
        }
        return result;
    };

    auto calcBudget = [&](int bomb) -> int {
        int budget = 0;
        for (auto& comp : comps) {
            int need = comp.x * bomb - comp.y;
            budget += buyOptimally(comp, need);
        }
        return budget;
    };

    int left = 0, right = 200000;
    while (left+1 < right) {
        int mid = (left+right)/2;
        if (calcBudget(mid) <= m) {
            left = mid;
        } else {
            right = mid;
        }
    }
    printf("%d", left);

    return 0;
}