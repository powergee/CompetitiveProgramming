#include <iostream>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (k == 1) {
        if (n == 2) {
            printf("NO");
        } else {
            for (int i = 0; i < 4; ++i) {
                printf("reverse 2 %d\n", n);
            }
            printf("swap 1 %d\n", n);
        }
    } else if (k == 2) {
        
    } else if (k == 3) {

    } else if (k == 4) {

    } else if (k == 5) {

    } else {
        printf("NO");
    }

    return 0;
}