#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Long n, g, k;
    std::cin >> n >> g >> k;

    std::vector<std::pair<Long, Long>> persistent, removable;
    for (int i = 0; i < n; ++i) {
        Long s, l, o;
        std::cin >> s >> l >> o;
        (o == 1LL ? removable : persistent).emplace_back(s, l);
    }

    auto isPossible = [&](Long t) -> bool {
        __int128_t sum = 0;
        for (auto p : persistent) {
            sum += __int128_t(p.first) * std::max(Long(1), t-p.second);
            if (sum > g) {
                return false;
            }
        }

        std::vector<__int128_t> cands;
        for (auto p : removable) {
            cands.push_back(__int128_t(p.first) * std::max(Long(1), t-p.second));
        }
        std::sort(cands.begin(), cands.end());
        for (int i = 0; i < Long(cands.size())-k && k < cands.size(); ++i) {
            sum += cands[i];
            if (sum > g) {
                return false;
            }
        }
        
        return true;
    };

    Long left = 0, right = INT64_MAX;
    while (left+1 < right) {
        Long mid = (left+right)/2;
        if (isPossible(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (isPossible(right)) {
        std::cout << right;
    } else {
        std::cout << left;
    }

    return 0;
}