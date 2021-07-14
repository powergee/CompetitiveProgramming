#include <iostream>
#include <algorithm>
#define UND (-__INT32_MAX__)

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, a, b;
        char str[101];
        scanf("%d %d %d", &n, &a, &b);
        scanf("%s", str);

        int segCount = 1;
        for (int i = 1; i < n; ++i) {
            if (str[i-1] != str[i]) {
                ++segCount;
            }
        }
        
        if (b >= 0) {
            printf("%d\n", a*n+b*n);
        } else {
            if (segCount % 2 == 1) {
                printf("%d\n", a*n + ((segCount+1)/2)*b);
            } else {
                printf("%d\n", a*n + ((segCount/2)+1)*b);
            }
        }
    }

    return 0;
}