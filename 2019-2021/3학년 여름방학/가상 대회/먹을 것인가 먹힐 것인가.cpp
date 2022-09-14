#include <iostream>
#include <algorithm>

int a[20000];
int b[20000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i) {
            scanf("%d", a+i);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", b+i);
        }

        std::sort(a, a+n);
        std::sort(b, b+m);

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            auto found = std::lower_bound(b, b+m, a[i]);
            answer += found-b;
        }

        printf("%d\n", answer);
    }

    return 0;
}