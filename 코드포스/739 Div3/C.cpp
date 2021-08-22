#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int k;
        scanf("%d", &k);

        int shellNum = -1;
        int end = -1;
        for (int i = 1; end == -1; ++i) {
            if ((i-1)*(i-1) < k && k <= i*i) {
                shellNum = i;
                end = i*i;
            }
        }

        int current = (shellNum-1)*(shellNum-1)+1;
        bool printed = false;
        for (int r = 1; r <= shellNum && !printed; ++r) {
            if (current == k) {
                printf("%d %d\n", r, shellNum);
                printed = true;
            }
            ++current;
        }

        for (int c = shellNum-1; c >= 1 && !printed; --c) {
            if (current == k) {
                printf("%d %d\n", shellNum, c);
                printed = true;
            }
            ++current;
        }
    }

    return 0;
}