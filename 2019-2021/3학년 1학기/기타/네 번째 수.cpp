#include <iostream>
#include <algorithm>

int main() {
    int a[3];
    for (int i = 0; i < 3; ++i) {
        scanf("%d", a+i);
    }

    std::sort(a, a+3);

    if (a[1]*2 == a[0]+a[2]) {
        printf("%d", a[0]-(a[1] - a[0]));
    } else if (a[1] - a[0] < a[2] - a[1]) {
        printf("%d", (a[2]+a[1])/2);
    } else {
        printf("%d", (a[0]+a[1])/2);
    }

    return 0;
}