#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::vector<int> arr(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
            total += arr[i];
        }

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            if (total <= arr[i]*n) {
                answer++;
            }
        }
        std::cout << answer << "/" << n << "\n";
    }

    return 0;
}