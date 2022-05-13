#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::string line;
        std::cin >> line;
        int n = line.size();

        std::vector<int> sum(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + (line[i-1] == '1' ? 1 : 0);
        }
        auto getSum = [&](int l, int r) -> int {
            return sum[r] - sum[l-1];
        };

        int answer = std::min(n-sum[n], sum[n]);
        for (int l = 1; l <= n; ++l) {
            auto getCost = [=](int r) -> int {
                return std::max(r-l+1-getSum(l, r), getSum(r+1, n)+getSum(1, l-1));
            };

            int low = l, high = n;
            while (high-low >= 10) {
                int p = (low*2 + high)/3;
                int q = (low + high*2)/3;
                if (getCost(p) <= getCost(q)) {
                    high = q;
                } else {
                    low = p;
                }
            }

            for (int r = low; r <= high; ++r) {
                answer = std::min(answer, getCost(r));
            }
        }

        std::cout << answer << "\n";
    }

    return 0;
}