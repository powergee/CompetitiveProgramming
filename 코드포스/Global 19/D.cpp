#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

enum Seletion { A, B };

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        Long squareSum = 0, sum = 0;
        std::vector<int> a(n+1, 0), b(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            squareSum += a[i]*a[i];
            sum += a[i];
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
            squareSum += b[i]*b[i];
            sum += b[i];
        }
        
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(10001, INT32_MIN));

        std::function<int(int, int)> findMinDiff = [&](int start, int prevDiff) -> int {
            if (start == n+1) {
                return prevDiff;
            }

            int& result = dp[start][prevDiff];
            if (result != INT32_MIN) {
                return result;
            }
            int currDiff = std::abs(a[start]-b[start]);
            result = std::min(findMinDiff(start+1, prevDiff+currDiff), findMinDiff(start+1, std::abs(prevDiff-currDiff)));
            return result;
        };

        int diff = findMinDiff(1, 0);
        printf("%lld\n", (n-2)*squareSum + ((sum-diff)/2)*((sum-diff)/2) + ((sum-diff)/2+diff)*((sum-diff)/2+diff));
    }

    return 0;
}