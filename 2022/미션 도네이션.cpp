#include <iostream>
#include <vector>
#include <tuple>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int m;
        std::cin >> m;
        std::vector<std::tuple<Long, Long, Long>> missions(m);
        
        for (int i = 0; i < m; ++i) {
            Long k, d, a;
            std::cin >> k >> d >> a;
            missions[i] = { k, d, a };
        }

        Long killed, died, assisted;
        std::cin >> killed >> died >> assisted;

        Long answer = 0;
        for (auto [k, d, a] : missions) {
            Long earned = k*killed - d*died + a*assisted;
            answer += std::max(0LL, earned);
        }
        std::cout << answer << "\n";
    }

    return 0;
}