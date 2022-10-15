#include <iostream>
#include <algorithm>

typedef long long Long;

const Long MOD = 1000000007LL;
Long dp[100001][3][3][3];

Long countCases(int longest, int d1, int d2, int d3) {
    if (longest < d1 || longest < d2 || longest < d3) {
        return 0;
    }
    int db = std::min(d1, std::min(d2, d3));
    if (db > 0) {
        return countCases(longest-db, d1-db, d2-db, d3-db);
    }
    if (longest == 0) {
        return d1 == 0 && d2 == 0 && d3 == 0 ? 1 : 0;
    }
    Long& result = dp[longest][d1][d2][d3];
    if (result != -1) {
        return result;
    }

    result = 0;
    if (longest >= 2) {
        if (d1 == db) {
            result += countCases(longest, d1+2, d2, d3);
        } else if (d2 == db) {
            result += countCases(longest, d1, d2+2, d3);
        } else if (d3 == db) {
            result += countCases(longest, d1, d2, d3+2);
        }
    }
    if (longest >= 1) {
        if (d1 == db && d2 == db) {
            result += countCases(longest, d1+1, d2+1, d3);
        } else if (d2 == db && d3 == db) {
            result += countCases(longest, d1, d2+1, d3+1);
        }
    }
    result %= MOD;
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(Long), -1LL);

    int T;
    std::cin >> T;

    while (T--) {
        int n, r, c;
        std::cin >> n >> r >> c;
        Long answer = 0;
        if (r == 1) {
            answer = countCases(c-1, 0, 0, 0)*countCases(n-c, 0, 0, 0)
                   + countCases(c-1, 0, 1, 1)*countCases(n-c, 0, 0, 0)
                   + countCases(c-1, 0, 0, 0)*countCases(n-c, 0, 1, 1)
                   + countCases(c-1, 0, 1, 0)*countCases(n-c, 0, 0, 1)
                   + countCases(c-1, 0, 0, 1)*countCases(n-c, 0, 1, 0);
        } else if (r == 2) {
            answer = countCases(c-1, 1, 0, 1)*countCases(n-c, 0, 0, 0)
                   + countCases(c-1, 0, 0, 0)*countCases(n-c, 1, 0, 1)
                   + countCases(c-1, 1, 0, 0)*countCases(n-c, 0, 0, 1)
                   + countCases(c-1, 0, 0, 1)*countCases(n-c, 1, 0, 0);
        } else {
            answer = countCases(c-1, 0, 0, 0)*countCases(n-c, 0, 0, 0)
                   + countCases(c-1, 1, 1, 0)*countCases(n-c, 0, 0, 0)
                   + countCases(c-1, 0, 0, 0)*countCases(n-c, 1, 1, 0)
                   + countCases(c-1, 1, 0, 0)*countCases(n-c, 0, 1, 0)
                   + countCases(c-1, 0, 1, 0)*countCases(n-c, 1, 0, 0);
        }
        answer %= MOD;
        std::cout << answer << "\n";
    }

    return 0;
}