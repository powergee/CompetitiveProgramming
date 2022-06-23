#include <iostream>
#include <functional>

void iterateCombWithDup(int n, int k, std::function<void(const std::vector<int>&)> callback) {
    std::vector<int> selected;
    selected.reserve(k);
    std::function<void(int)> searchCases = [&](int start) {
        if (selected.size() == k) {
            callback(selected);
        } else if (start < n) {
            selected.push_back(start);
            searchCases(start);
            selected.pop_back();
            searchCases(start+1);
        }
    };
    searchCases(0);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    iterateCombWithDup(n, k, [](const std::vector<int>& arr) {
        for (int v : arr) {
            printf("%d ", v+1);
        }
        printf("\n");
    });
    return 0;
}