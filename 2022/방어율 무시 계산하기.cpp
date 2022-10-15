#include <iostream>
#include <algorithm>
#include <iomanip>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(10);

    int n;
    std::cin >> n;
    double curr = 0;

    for (int i = 0; i < n; ++i) {
        double drink;
        std::cin >> drink;
        curr = 1 - (1-curr) * (1-drink/100);
        std::cout << curr * 100 << "\n";
    }

    return 0;
}