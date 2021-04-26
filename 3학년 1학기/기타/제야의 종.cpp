#include <iostream>
#include <algorithm>

bool heard[1000][100];
bool sorted[1000][100];
std::pair<int, int> colCount[100];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int hVal;
            scanf("%d", &hVal);
            heard[i][j] = (hVal == 1);
        }
    }

    for (int j = 0; j < m; ++j) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (heard[i][j]) {
                ++count;
            }
        }
        colCount[j] = {count, j};
    }

    std::sort(colCount, colCount+m);
    for (int j = 0; j < m; ++j) {
        int from = colCount[j].second;
        for (int i = 0; i < n; ++i) {
            sorted[i][j] = heard[i][from];
        }
    }

    bool yes = true;
    for (int j = 0; j < m-1; ++j) {
        for (int i = 0; i < n; ++i) {
            if ((sorted[i][j] || sorted[i][j+1]) != sorted[i][j+1]) {
                yes = false;
            }
        }
    }

    if (yes) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}