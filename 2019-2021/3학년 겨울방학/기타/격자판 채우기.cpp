#include <iostream>
#include <vector>
#include <algorithm>

bool isFilled(int mask, int index) {
    return (mask & (1<<index)) > 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> dp(n, std::vector<int>(1<<m, 0));
    std::vector<std::vector<int>> next(1<<m);

    auto getCases = [=](int origin) -> std::vector<int> {
		std::vector<int> results;
		std::function<void(int, int, int)> iterateCases = [&](int curr, int next, int start) {
			if (start == m) {
				results.push_back(next);
			} else if (!isFilled(curr, start)) {
                iterateCases(curr|(1<<start), next|(1<<start), start+1);
				if (start+1 < m && !isFilled(curr, start+1)) {
					iterateCases(curr|(1<<start)|(1<<(start+1)), next, start+2);
				}
			} else {
                iterateCases(curr, next, start+1);
            }
		};
		iterateCases(origin, 0, 0);
		return results;
	};

    for (int filled = 0; filled < (1<<m); ++filled) {
        next[filled] = getCases(filled);
        dp[0][filled] = 1;
        for (int i = 0; i < m;) {
            if (isFilled(filled, i)) {
                ++i;
                continue;
            } else if (m-1 <= i || isFilled(filled, i+1)) {
                dp[0][filled] = 0;
                break;
            } else {
                i += 2;
            }
        }
    }

    for (int remain = 1; remain < n; ++remain) {
        for (int filled = 0; filled < (1<<m); ++filled) {
            for (int nf : next[filled]) {
                dp[remain][filled] += dp[remain-1][nf];
                dp[remain][filled] %= 9901;
            }
        }
    }

    printf("%d", dp[n-1][0]);

    return 0;
}