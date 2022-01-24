#include <iostream>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> aff(2*n, std::vector<int>(2*n));
    for (int i = 0; i < 2*n; ++i) {
        for (int j = i+1; j < 2*n; ++j) {
            scanf("%d", &aff[i][j]);
        }
    }

    int answer = 0;
    std::function<void(int, int)> assignGroups = [&](int mask, int prevAff) -> void {
        std::vector<int> exist;
        for (int i = 0; i < 2*n; ++i) {
            if ((mask & (1<<i)) == 0) {
                exist.push_back(i);
            }
        }

        if (exist.empty()) {
            answer = std::max(answer, prevAff);
        } else {
            for (int i = 1; i < exist.size(); ++i) {
                assignGroups(mask | (1<<exist[0]) | (1<<exist[i]), prevAff ^ aff[exist[0]][exist[i]]);
            }
        }
    };
    assignGroups(0, 0);

    printf("%d", answer);

    return 0;
}