#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> count(n+1, 0);
        for (int i = 0; i < n; ++i) {
            int v;
            scanf("%d", &v);
            count[v]++;
        }

        int answer = -1;
        for (int i = 0; i <= n; ++i) {
            if (count[i] >= 3) {
                answer = i;
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}