#include <iostream>
#include <vector>
#include <functional>

typedef long long Long;

const Long MOD = 100000007;

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<Long> dp((n+m+1)*(n+m+1)*(k+1), -1LL);
    std::function<Long(int, int, int)> countCases = [&](int mine, int oppo, int stage) -> Long {
        Long& result = dp[(m+1)*(k+1)*mine + (k+1)*oppo + stage];
        if (result != -1) {
            return result;
        } else if (mine == 0 || oppo == 0) {
            return result = 1;
        } else if (stage == k) {
            return result = 0;
        }

        result = countCases(mine-1, oppo+1, stage+1) + countCases(mine+1, oppo-1, stage+1) + countCases(mine, oppo, stage+1);
        result %= MOD;
        return result;
    };

    std::cout << countCases(n, m, 0);

    return 0;
}