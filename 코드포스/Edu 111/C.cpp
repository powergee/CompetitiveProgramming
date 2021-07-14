#include <iostream>
#include <algorithm>

int arr[200000];

bool isBadTriplet(int a1, int a2, int a3) {
    int min = std::min(a1, a3);
    int max = std::max(a1, a3);
    return min <= a2 && a2 <= max;
}

bool containsBadTriplet(int left, int right) {
    for (int i = left; i <= right-2; ++i) {
        for (int j = i+1; j <= right-1; ++j) {
            for (int k = j+1; k <= right; ++k) {
                if (isBadTriplet(arr[i], arr[j], arr[k])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        int answer = 2*n-1;
        for (int i = 0; i+2 < n; ++i) {
            if (!containsBadTriplet(i, i+2)) {
                ++answer;
            }
        }
        for (int i = 0; i+3 < n; ++i) {
            if (!containsBadTriplet(i, i+3)) {
                ++answer;
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}