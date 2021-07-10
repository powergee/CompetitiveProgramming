#include <iostream>
#include <algorithm>
#include <vector>

int ac1[300], ac2[300];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int k, n, m;
        scanf("%d %d %d", &k, &n, &m);

        for (int i = 0; i < n; ++i) {
            scanf("%d", ac1+i);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", ac2+i);
        }

        std::vector<int> answer;
        int idx1 = 0, idx2 = 0;
        int lines = k;

        while (idx1 < n || idx2 < m) {
            if (idx1 < n && ac1[idx1] == 0) {
                answer.push_back(0);
                ++lines;
                ++idx1;
            } else if (idx2 < m && ac2[idx2] == 0) {
                answer.push_back(0);
                ++lines;
                ++idx2;
            } else if (idx1 < n && ac1[idx1] <= lines) {
                answer.push_back(ac1[idx1++]);
            } else if (idx2 < m && ac2[idx2] <= lines) {
                answer.push_back(ac2[idx2++]);
            } else {
                break;
            }
        }

        if ((int)answer.size() == n+m) {
            for (int v : answer) {
                printf("%d ", v);
            }
            printf("\n");
        } else {
            printf("-1\n");
        }
    }
    
    return 0;
}