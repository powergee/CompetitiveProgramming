#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    int min = INT32_MAX, max = INT32_MIN;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        min = std::min(min, v);
        max = std::max(max, v);
    }

    std::cout << (max-min) * 2;

    return 0;
}