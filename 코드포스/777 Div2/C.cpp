#include <iostream>
#include <vector>
#include <tuple>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        
        std::vector<std::vector<int>> map(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            char line[m+1];
            scanf("%s", line);
            for (int j = 0; j < m; ++j) {
                map[i][j] = line[j] == '1' ? 1 : 0;
            }
        }

        if (map[0][0] == 1) {
            printf("-1\n");
            continue;
        }

        std::vector<std::tuple<int, int, int, int>> answer;
        for (int i = n-1; i >= 0; --i) {
            for (int j = m-2; j >= 0; --j) {
                if (map[i][j+1] == 1) {
                    answer.emplace_back(i, j, i, j+1);
                }
            }
            if (i >= 1 && map[i][0] == 1) {
                answer.emplace_back(i-1, 0, i, 0);
            }
        }

        printf("%d\n", (int)answer.size());
        for (auto t : answer) {
            auto [r1, c1, r2, c2] = t;
            printf("%d %d %d %d\n", r1+1, c1+1, r2+1, c2+1);
        }
    }

    return 0;
}