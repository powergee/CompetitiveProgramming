#include <iostream>
#include <algorithm>

int a[200000];
int b[200000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", b+i);
    }

    std::sort(b, b+m);
    
    int answer = __INT32_MAX__;
    for (int i = 0; i < n; ++i) {
        int* ptr = std::lower_bound(b, b+m, a[i]);

        if (ptr == b+m) {
            answer = std::min(answer, std::abs(*(ptr-1) - a[i]));
        } else if (ptr == b) {
            answer = std::min(answer, std::abs(*ptr - a[i]));
        } else {
            int curr = std::min(std::abs(*(ptr-1) - a[i]), std::abs(*ptr - a[i]));
            answer = std::min(answer, curr);
        }
    }

    printf("%d", answer);

    return 0;
}