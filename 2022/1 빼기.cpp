#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    std::cin >> n;

    std::function<int(int)> getMinCost;
    getMinCost = [&](int n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        }

        auto str = std::to_string(n);
        if (str.front() == '1') {
            return 1 + getMinCost(std::stoi(str.substr(1)));
        }
        for (int i = 1; i+1 < str.size(); ++i) {
            if (str[i] == '1') {
                return 1 + getMinCost(std::stoi(str.substr(0, i) + str.substr(i+1)));
            }
        }

        int cost = 0;
        while (n % 10 != 1) {
            n -= 1;
            cost++;
        }
        if (n == 1) {
            return cost + 1;
        } else {
            return cost + 1 + getMinCost(n/10);
        }
    };

    std::cout << getMinCost(n);

    return 0;
}