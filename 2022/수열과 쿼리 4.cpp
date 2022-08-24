#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <cassert>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n+1, 0);
    std::vector<std::vector<int>> pos(k+1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        pos[arr[i]].push_back(i);
    }
    int SQRT = int(std::sqrt(n))+1;

    int q;
    std::cin >> q;
    using Query = std::tuple<int, int, int>;
    std::vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries[i] = { l, r, i };
    }

    std::sort(queries.begin(), queries.end(), [=](const Query& q1, const Query& q2) {
        auto [l1, r1, i1] = q1;
        auto [l2, r2, i2] = q2;
        int g1 = r1/SQRT;
        int g2 = r2/SQRT;
        if (g1 != g2) {
            return g1 < g2;
        } else {
            return l1 < l2;
        }
    });

    std::vector<int> countPerGroup(n/SQRT+1, 0), countPerCell(n+1, 0);

    auto addCount = [&](int val, int cnt) {
        countPerCell[val] += cnt;
        countPerGroup[val/SQRT] += cnt;
    };

    std::vector<std::pair<int, int>> bucket(k+1, {0, -1});
    std::pair<int, int> curr = { 1, 0 };
    std::vector<int> answer(q, -1);

    for (auto [ql, qr, qi] : queries) {
        // expand first
        while (curr.second < qr) {
            curr.second++;
            int val = arr[curr.second];
            auto& [bl, br] = bucket[val];
            if (bl <= br) {
                addCount(pos[val][br] - pos[val][bl], -1);
            }
            addCount(pos[val][++br] - pos[val][bl], 1);
        }
        while (ql < curr.first) {
            curr.first--;
            int val = arr[curr.first];
            auto& [bl, br] = bucket[val];
            if (bl <= br) {
                addCount(pos[val][br] - pos[val][bl], -1);
            }
            addCount(pos[val][br] - pos[val][--bl], 1);
        }

        // shrink later
        while (qr < curr.second) {
            int val = arr[curr.second];
            auto& [bl, br] = bucket[val];
            addCount(pos[val][br] - pos[val][bl], -1);
            if (bl <= --br) {
                addCount(pos[val][br] - pos[val][bl], 1);
            }
            curr.second--;
        }
        while (curr.first < ql) {
            int val = arr[curr.first];
            auto& [bl, br] = bucket[val];
            addCount(pos[val][br] - pos[val][bl], -1);
            if (++bl <= br) {
                addCount(pos[val][br] - pos[val][bl], 1);
            }
            curr.first++;
        }
        
        for (int i = n/SQRT; i >= 0 && answer[qi] == -1; --i) {
            if (countPerGroup[i] == 0) {
                continue;
            }
            for (int j = std::min((i+1)*SQRT-1, n); j >= i*SQRT; --j) {
                if (countPerCell[j]) {
                    answer[qi] = j;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        std::cout << answer[i] << "\n";
    }

    return 0;
}