#include <iostream>
#include <vector>

int main() {
    int w, n;
    scanf("%d %d", &w, &n);
    std::vector<int> arr(n);
    std::vector<int> pairs(400001);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    bool exist = false;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int target = w-arr[i]-arr[j];
            if (0 <= target && target < pairs.size() && pairs[target] > 0) {
                exist = true;
                goto breakAll;
            }
        }
        for (int j = 0; j < i; ++j) {
            pairs[arr[i]+arr[j]]++;
        }
    } breakAll:

    printf(exist ? "YES" : "NO");

    return 0;
}