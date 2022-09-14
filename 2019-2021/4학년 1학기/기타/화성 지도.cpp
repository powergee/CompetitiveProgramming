#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

using Long = long long;

int main() {
    const int MAX = 30002;
    const int SQRT = 174;
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::tuple<int, int, int>>> diff(MAX);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        diff[x1].emplace_back(y1, y2, 1);
        diff[x2].emplace_back(y1, y2, -1);
    }

    Long answer = 0;
    int vals[SQRT][SQRT] = {0};
    int sorted[SQRT][SQRT] = {0};
    int shift[SQRT] = {0};
    for (int i = 0; i < MAX; ++i) {
        for (auto [l, r, add] : diff[i]) {
            int lb = l / SQRT;
            int rb = r / SQRT;
            if (lb == rb) {
                int b = lb;
                for (int i = l-b*SQRT; i < r-b*SQRT; ++i) {
                    vals[b][i] += add;
                }
                std::copy(vals[b], vals[b]+SQRT, sorted[b]);
                std::sort(sorted[b], sorted[b]+SQRT);
            } else {
                for (int i = l-lb*SQRT; i < SQRT; ++i) {
                    vals[lb][i] += add;
                }
                std::copy(vals[lb], vals[lb]+SQRT, sorted[lb]);
                std::sort(sorted[lb], sorted[lb]+SQRT);

                for (int i = 0; i < r-rb*SQRT; ++i) {
                    vals[rb][i] += add;
                }
                std::copy(vals[rb], vals[rb]+SQRT, sorted[rb]);
                std::sort(sorted[rb], sorted[rb]+SQRT);

                for (int i = lb+1; i <= rb-1; ++i) {
                    shift[i] += add;
                }
            }
        }
        
        for (int i = 0; i < SQRT; ++i) {
            auto it = std::upper_bound(sorted[i], sorted[i]+SQRT, -shift[i]);
            answer += (sorted[i]+SQRT) - it;
        }
    }

    std::cout << answer;

    return 0;
}