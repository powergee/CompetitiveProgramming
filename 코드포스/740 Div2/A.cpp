#include <iostream>

bool isSorted(int* arr, int length) {
    for (int i = 0; i < length-1; ++i) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int origin[n];

        for (int i = 0; i < n; ++i) {
            scanf("%d", &origin[i]);
        }
        
        int count = 0;
        for (int i = 1; !isSorted(origin, n); ++i) {
            int start = (i % 2 == 0 ? 1 : 0);
            for (int j = start; j < n-1; j += 2) {
                if (origin[j] > origin[j+1]) {
                    std::swap(origin[j], origin[j+1]);
                }
            }
            ++count;
        }

        printf("%d\n", count);
    }

    return 0;
}