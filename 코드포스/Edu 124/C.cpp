#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<std::vector<Long>> row(2, std::vector<Long>(n));
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%lld", &row[i][j]);
            }
        }

        std::vector<std::vector<int>> conn(2, std::vector<int>(2, 0));
        std::function<Long()> iterateStates = [&]() -> Long {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    if (conn[i][j] == 0) {
                        Long cost = INT64_MAX;
                        int curr = row[i][j == 0 ? 0 : n-1];
                        int oppoRow = (i == 0 ? 1 : 0);

                        // 상대편의 최소비용과 연결하기
                        {
                            Long c1 = std::abs(row[oppoRow][1] - curr);
                            for (int k = 2; k < n-1; ++k) {
                                c1 = std::min(c1, std::abs(row[oppoRow][k] - curr));
                            }
                            conn[i][j] = 1;
                            cost = std::min(cost, c1+iterateStates());
                            conn[i][j] = 0;
                        }

                        // 상대편의 Left와 연결하기
                        {
                            Long c2 = std::abs(row[oppoRow][0] - curr);
                            int prevOppoLeftConn = conn[oppoRow][0];
                            conn[i][j] = 1;
                            conn[oppoRow][0] = 1;
                            cost = std::min(cost, c2+iterateStates());
                            conn[i][j] = 0;
                            conn[oppoRow][0] = prevOppoLeftConn;
                        }

                        // 상대편의 Right와 연결하기
                        {
                            Long c3 = std::abs(row[oppoRow][n-1] - curr);
                            int prevOppoRightConn = conn[oppoRow][1];
                            conn[i][j] = 1;
                            conn[oppoRow][1] = 1;
                            cost = std::min(cost, c3+iterateStates());
                            conn[i][j] = 0;
                            conn[oppoRow][1] = prevOppoRightConn;
                        }

                        return cost;
                    }
                }
            }
            return 0;
        };

        printf("%lld\n", iterateStates());
    }

    return 0;
}