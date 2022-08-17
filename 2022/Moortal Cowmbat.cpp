#include <iostream>
#include <functional>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    std::cin >> n >> m >> k;

    std::string combo;
    std::cin >> combo;

    std::vector<std::vector<int>> dist(m, std::vector<int>(m));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> dist[i][j];
        }
    }

    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    std::vector<std::vector<int>> costSum(m, std::vector<int>(n+1, 0));
    for (int t = 0; t < m; ++t) {
        for (int i = 1; i <= n; ++i) {
            costSum[t][i] = costSum[t][i-1] + dist[combo[i-1]-'a'][t];
        }
    }

    using Long = long long;
    std::vector<Long> fullDp(n+1, -1);
    std::vector<std::vector<Long>> partialDp(n+1, std::vector<Long>(m, -1));

    std::function<Long(int)> getFullMinCost;
    std::function<Long(int, int)> getPartialMinCost;
    
    getFullMinCost = [&](int start) -> Long {
        if (start > n) {
            return 0;
        } else if (fullDp[start] != -1) {
            return fullDp[start];
        } else if (n < start+k-1) {
            return fullDp[start] = INT32_MAX;
        } else {
            fullDp[start] = INT32_MAX;
            for (int ch = 0; ch < m; ++ch) {
                fullDp[start] = std::min(fullDp[start], costSum[ch][start+k-1]-costSum[ch][start-1] + getPartialMinCost(start+k, ch));
            }
            return fullDp[start];
        }
    };

    getPartialMinCost = [&](int start, int ch) -> Long {
        if (start > n) {
            return 0;
        } else if (partialDp[start][ch] != -1) {
            return partialDp[start][ch];
        } else {
            return partialDp[start][ch] = std::min(
                getFullMinCost(start),
                costSum[ch][start]-costSum[ch][start-1] + getPartialMinCost(start+1, ch)
            );
        }
    };

    std::cout << getFullMinCost(1);

    return 0;
}