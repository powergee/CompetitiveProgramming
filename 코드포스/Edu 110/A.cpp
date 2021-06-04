#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a[4];
        scanf("%d %d %d %d", a+0, a+1, a+2, a+3);

        int w[2];
        w[0] = std::max(a[0], a[1]);
        w[1] = std::max(a[2], a[3]);

        std::sort(a, a+4);
        std::sort(w, w+2);
        
        if (a[2] == w[0] && a[3] == w[1]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}