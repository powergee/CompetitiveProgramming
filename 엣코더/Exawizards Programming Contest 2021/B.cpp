#include <iostream>

int main() {
    int n, p;
    scanf("%d %d", &n, &p);

    int count = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        if (val < p) {
            ++count;
        }
    }

    printf("%d", count);

    return 0;
}