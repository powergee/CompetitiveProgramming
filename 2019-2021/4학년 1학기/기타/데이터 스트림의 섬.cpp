#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int t;
        scanf("%d", &t);

        int arr[12];
        for (int i = 0; i < 12; ++i) {
            scanf("%d", arr+i);
        }

        int count = 0;
        for (int i = 1; i < 11; ++i) {
            int min = arr[i];
            for (int j = i; j < 11; ++j) {
                min = std::min(min, arr[j]);
                if (min > arr[i-1] && min > arr[j+1]) {
                    ++count;
                }
            }
        }

        printf("%d %d\n", t, count);
    }

    return 0;
}