#include <iostream>
#include <functional>

void iterateComb(int n, int k, std::function<void(const std::vector<int>&)> callback) {
    std::vector<int> selected;
    selected.reserve(k);
    std::function<void(int)> searchCases = [&](int start) {
        if (selected.size() == k) {
            callback(selected);
        } else if (n-start < k-selected.size()) {
            return;
        } else {
            selected.push_back(start);
            searchCases(start+1);
            selected.pop_back();
            searchCases(start+1);
        }
    };
    searchCases(0);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    std::sort(arr.begin(), arr.end());

    iterateComb(n, k, [&](const std::vector<int>& sel) {
        for (int v : sel) {
            printf("%d ", arr[v]);
        }
        printf("\n");
    });
    return 0;
}