#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::string> lines(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> lines[i];
        }
        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            std::cout << *it << "\n";
        }
    }

    return 0;
}