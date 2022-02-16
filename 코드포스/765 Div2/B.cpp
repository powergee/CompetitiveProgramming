#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<std::vector<int>> pos(150001);
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            pos[val].push_back(i);
        }

        int answer = -1;
        for (int i = 0; i < 150001; ++i) {
            for (int j = 0; j+1 < pos[i].size(); ++j) {
                answer = std::max(answer, pos[i][j] - pos[i][j+1] + n);
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}