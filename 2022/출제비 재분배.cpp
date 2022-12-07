#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> profit(n+m, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> profit[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+m; ++j) {
            int diff;
            std::cin >> diff;
            profit[j] += diff;
            profit[i] -= diff;
        }
    }

    for (int i = 0; i < n+m; ++i) {
        std::cout << profit[i] << " ";
    }

    return 0;
}