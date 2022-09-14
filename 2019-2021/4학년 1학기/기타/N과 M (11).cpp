#include <iostream>
#include <functional>
#include <set>

void iteratePermWithDup(int n, int k, std::function<void(const std::vector<int>&)> callback) {
    std::vector<int> selected;
    selected.reserve(k);
    std::function<void()> searchCases = [&]() {
        if (selected.size() == k) {
            callback(selected);
        } else {
            for (int i = 0; i < n; ++i) {
                selected.push_back(i);
                searchCases();
                selected.pop_back();
            }
        }
    };
    searchCases();
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    std::sort(arr.begin(), arr.end());

    std::set<std::vector<int>> answers;
    iteratePermWithDup(n, k, [&](const std::vector<int>& sel) {
        std::vector<int> trans(k);
        for (int i = 0; i < k; ++i) {
            trans[i] = arr[sel[i]];
        }
        answers.insert(trans);
    });
    for (auto ans : answers) {
        for (int v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}