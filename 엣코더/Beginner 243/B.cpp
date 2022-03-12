#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b[i]);
    }

    int same = 0, different = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == b[j]) {
                (i == j ? same : different)++;
            }
        }
    }

    printf("%d\n%d", same, different);

    return 0;
}