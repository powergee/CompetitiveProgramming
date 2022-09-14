#include <iostream>

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    int sum = 0;
    int comp = 0;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        sum += val;
        if (sum <= t) {
            ++comp;
        } else {
            break;
        }
    }

    printf("%d", comp);

    return 0;
}