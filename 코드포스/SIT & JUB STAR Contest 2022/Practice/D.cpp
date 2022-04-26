#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    int half = 0, one = 0;
    for (int i = 0; i < n; ++i) {
        int w;
        scanf("%d", &w);
        if (w == 50) {
            half++;
        } else {
            one++;
        }
    }

    int min = std::min(half, one);
    printf("%d", min + (half-min)/3+((half-min)%3 > 0 ? 1 : 0) + (one-min));

    return 0;
}