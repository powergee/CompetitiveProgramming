#include <iostream>

int main() {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::pair<int, int> GOALS[] = {
        { 1, 2 }, { 2, 1 },
        { -1, 2 }, { -2, 1 },
        { -1, -2 }, { -2, -1 },
        { 1, -2 }, { 2, -1 },
    };

    bool yes = false;
    for (auto p : GOALS) {
        for (auto q : GOALS) {
            if (p == q) {
                continue;
            }
            int dist1[] = { p.first-x1, p.second-y1 };
            int dist2[] = { q.first-x2, q.second-y2 };
            bool different = false;
            for (int i = 0; i < 2; ++i) {
                if (dist1[i] != dist2[i]) {
                    different = true;
                    break;
                }
            }
            if (!different) {
                yes = true;
                goto END;
            }
        }
    }
    END:

    printf(yes ? "Yes" : "No");

    return 0;
}