#include <iostream>
#include <unordered_set>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n], sum = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        sum += arr[i];
    }

    std::unordered_set<int> set;
    for (int mask = 1; mask < (1<<n); ++mask) {
        int curr = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1<<i)) {
                curr += arr[i];
            }
        }
        set.insert(curr);
    }

    printf("%d", sum - int(set.size()));
    return 0;
}