#include <iostream>
#include <string>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d:\n", t);
        int r, c;
        scanf("%d %d", &r, &c);
        for (int i = 0; i < r*2+1; ++i) {
            for (int j = 0; j < c*2+1; ++j) {
                if (i < 2 && j < 2) {
                    putchar('.');
                } else if (i % 2) {
                    if (j % 2) {
                        putchar('.');
                    } else {
                        putchar('|');
                    }
                } else {
                    if (j % 2) {
                        putchar('-');
                    } else {
                        putchar('+');
                    }
                }
            }
            putchar('\n');
        }
    }
    
    return 0;
}