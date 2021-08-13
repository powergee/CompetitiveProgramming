#include <iostream>
#include <queue>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::queue<int> easy[n];
    for (int i = 0; i < n; ++i) {
        int count;
        scanf("%d", &count);
        for (int j = 0; j < count; ++j) {
            int p;
            scanf("%d", &p);
            easy[i].push(p);
        }
    }

    int selected = 0;
    int total = 0;
    while (selected < k) {
        bool runOutOfProblems = true;
        for (int i = 0; i < n && selected < k; ++i) {
            int p;
            if (easy[i].empty()) {
                p = 50;
            } else {
                runOutOfProblems = false;
                p = easy[i].front();
                easy[i].pop();
            }
            if (total <= p) {
                selected++;
                total += p;
            }
        }

        if (runOutOfProblems) {
            total += (k-selected) * 50;
            break;
        }
    }

    printf("%d", total);

    return 0;
}