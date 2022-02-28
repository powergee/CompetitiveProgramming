#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && (j <= i || arr[i] == arr[j])) {
            ++j;
        }
        printf("%d ", j == n ? -1 : j+1);
    }

    return 0;
}