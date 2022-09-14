#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> row(n);
    std::priority_queue<std::pair<int, int>> col;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &row[i]);
    }
    for (int i = 0; i < n; ++i) {
        int c;
        scanf("%d", &c);
        if (c) {
            col.emplace(c, i);
        }
    }

    bool possible = true;
    for (int i = 0; i < n; ++i) {
        if (col.size() < row[i]) {
            possible = false;
            break;
        }

        std::vector<std::pair<int, int>> toAdd;
        while (toAdd.size() < row[i]) {
            toAdd.push_back(col.top());
            col.pop();
        }

        for (auto add : toAdd) {
            matrix[i][add.second]++;
            if (--add.first) {
                col.push(add);
            }
        }
    }
    if (col.size() > 0) {
        possible = false;
    }

    if (possible) {
        printf("1\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%d", matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("-1\n");
    }

    return 0;
}