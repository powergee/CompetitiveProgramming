#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::vector<int> arr(n);
        std::for_each(arr.begin(), arr.end(), [](int& v) { std::cin >> v; });
        std::vector<int> sorted = arr;
        std::sort(sorted.begin(), sorted.end());
        if (arr == sorted) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
        }
    }

    return 0;
}