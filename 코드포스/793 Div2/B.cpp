#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    int answer = INT32_MAX;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (arr[i] != i) {
            answer = answer & arr[i];
        }
    }

    std::cout << answer << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}