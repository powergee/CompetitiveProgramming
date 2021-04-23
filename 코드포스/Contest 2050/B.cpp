#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>

int answer[100][100];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<std::multiset<int>> rowsMin(n);
        std::vector<std::multiset<int, std::greater<int>>> rowsMax(n);

        

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int b;
                scanf("%d", &b);
                rowsMax[i].insert(b);
                rowsMin[i].insert(b);
            }
        }

        for (int i = 0; i < m; ++i) {
            int minVal = __INT32_MAX__;
            int minRowIdx = -1;
            for (int j = 0; j < n; ++j) {
                int minOfRow = *rowsMin[j].begin();
                if (minOfRow < minVal) {
                    minRowIdx = j;
                    minVal = minOfRow;
                }
            }

            answer[minRowIdx][i] = minVal;
            rowsMin[minRowIdx].erase(rowsMin[minRowIdx].find(minVal));
            rowsMax[minRowIdx].erase(rowsMax[minRowIdx].find(minVal));

            for (int j = 0; j < n; ++j) {
                if (j == minRowIdx) {
                    continue;
                }

                int maxOfRow = *rowsMax[j].begin();
                answer[j][i] = maxOfRow;
                rowsMin[j].erase(rowsMin[j].find(maxOfRow));
                rowsMax[j].erase(rowsMax[j].find(maxOfRow));
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%d ", answer[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}