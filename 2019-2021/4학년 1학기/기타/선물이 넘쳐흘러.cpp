#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int b, n, m;
    std::cin >> b >> n >> m;

    std::vector<std::tuple<int, int, int>> workers(n);
    std::vector<int> endTime(n, 0);

    for (int i = 0; i < n; ++i) {
        int r, c, t;
        std::cin >> r >> c >> t;
        workers[i] = { r, c, t };
    }

    int answer = 0, maxTime = 3*b+m;
    std::vector<std::vector<bool>> map(b, std::vector<bool>(b, false));
    for (int t = 0; t < maxTime; ++t) {
        for (int i = 0; i+1 < b; ++i) {
            map[b-1][i] = map[b-1][i+1];
        }
        for (int i = b-1; i > 0; --i) {
            map[i][b-1] = map[i-1][b-1];
        }
        for (int i = b-1; i > 0; --i) {
            map[0][i] = map[0][i-1];
        }
        
        if (m > 0) {
            map[0][0] = true;
            m--;
        } else {
            map[0][0] = false;
        }

        for (int i = 0; i < n; ++i) {
            auto [r, c, dur] = workers[i];
            if (endTime[i] <= t) {
                const int dr[] = {1, 0, -1};
                const int dc[] = {0, 1, 0};
                for (int j = 0; j < 3; ++j) {
                    int nr = r+dr[j];
                    int nc = c+dc[j];
                    if (map[nr][nc]) {
                        map[nr][nc] = false;
                        endTime[i] = dur + t;
                        answer++;
                        break;
                    }
                }
            }
        }
    }
    std::cout << answer << "\n";

    return 0;
}