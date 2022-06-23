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
    iterateComb(n, k, [](const std::vector<int>& arr) {
        for (int v : arr) {
            printf("%d ", v+1);
        }
        printf("\n");
    });
    return 0;
}