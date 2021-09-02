#include <iostream>
#include <map>
#include <set>

char map[50][51];

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }

        std::map<int, std::set<std::string>> solutions;
        for (int r = 0; r < n; ++r) {
            bool valid = true;
            int blanks = 0;
            std::string selection(n*n, 0);
            for (int c = 0; c < n; ++c) {
                if (map[r][c] == '.') {
                    ++blanks;
                    selection[n*r + c] = 1;
                } else if (map[r][c] == 'O') {
                    valid = false;
                }
            }
            if (valid) {
                solutions[blanks].insert(selection);
            }
        }

        for (int c = 0; c < n; ++c) {
            bool valid = true;
            int blanks = 0;
            std::string selection(n*n, 0);
            for (int r = 0; r < n; ++r) {
                if (map[r][c] == '.') {
                    ++blanks;
                    selection[n*r + c] = 1;
                } else if (map[r][c] == 'O') {
                    valid = false;
                }
            }
            if (valid) {
                solutions[blanks].insert(selection);
            }
        }

        printf("Case #%d: ", t);
        if (solutions.empty()) {
            printf("Impossible\n");
        } else {
            auto p = *solutions.begin();
            printf("%d %d\n", p.first, (int)p.second.size());
        }
    }

    return 0;
}