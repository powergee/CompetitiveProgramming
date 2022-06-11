#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        std::string line;
        std::cin >> line;
        char max = 0;
        for (char ch : line) {
            max = std::max(max, ch);
        }
        std::cout << max << "\n";
    }

    return 0;
}