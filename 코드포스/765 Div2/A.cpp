#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, l;
        scanf("%d %d", &n, &l);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        unsigned result = 0;
        for (unsigned e = 1; e < (1U<<31); e <<= 1) {
            unsigned popCount = 0;
            for (int i = 0; i < n; ++i) {
                if (arr[i] & e) {
                    popCount++;
                }
            }
            if (popCount*2 > n) {
                result |= e;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}