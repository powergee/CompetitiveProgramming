#include <iostream>
#include <vector>

bool areSame(int* a, int* b, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int a[n], b[n];
        int sum[2] = {0, 0};
        for (int i = 0; i < n; ++i) {
            scanf("%d", a+i);
            sum[0] += a[i];
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", b+i);
            sum[1] += b[i];
        }

        if (sum[0] == sum[1]) {
            std::vector<std::pair<int, int>> answer;
            bool possible = true;

            while (!areSame(a, b, n) && possible) {
                int bigger = 0, smaller = 0;
                while (bigger < n && a[bigger] <= b[bigger]) {
                    bigger++;
                }
                while (smaller < n && b[smaller] <= a[smaller]) {
                    smaller++;
                }

                if (bigger == n || smaller == n) {
                    possible = false;
                } else {
                    a[bigger]--;
                    a[smaller]++;
                    answer.emplace_back(bigger, smaller);
                }
            }

            printf("%d\n", (int)answer.size());
            for (auto p : answer) {
                printf("%d %d\n", p.first+1, p.second+1);
            }
        } else {
            printf("-1\n");
        }
    }

    return 0;
}