#include <iostream>
#include <vector>

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

        bool yes = true;
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < m-1; ++j) {
                int count = 0;
                for (int di = 0; di < 2; ++di) {
                    for (int dj = 0; dj < 2; ++dj) {
                        count += map[i+di][j+dj];
                    }
                }
                if (count == 3) {
                    yes = false;
                }
            }
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}