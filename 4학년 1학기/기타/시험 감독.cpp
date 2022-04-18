#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int b, c;
    std::cin >> b >> c;

    long long result = n;
    for (int i = 0; i < n; ++i) {
        int spare = std::max(arr[i]-b, 0);
        result += spare/c + (spare%c == 0 ? 0 : 1);
    }

    std::cout << result;

    return 0;
}