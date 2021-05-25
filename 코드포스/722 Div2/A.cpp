#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, arr[100];
        scanf("%d", &n);

        int min = __INT32_MAX__;
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            min = std::min(min, arr[i]);
        }

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] != min) {
                ++answer;
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}