#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, b, a;
    std::cin >> n >> b >> a;

    std::vector<int> price(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> price[i];
    }

    std::sort(price.begin(), price.end());
    
    auto isPossible = [&](int count) -> bool {
        int currBudget = b;
        int saleStart = count - a;
        for (int i = 0; i < count; ++i) {
            int cost = saleStart <= i ? price[i]/2 : price[i];
            if (currBudget < cost) {
                return false;
            } else {
                currBudget -= cost;
            }
        }
        return true;
    };

    int left = 0, right = n;
    while (left+1 < right) {
        int mid = (left + right) / 2;
        if (isPossible(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (isPossible(right)) {
        left = right;
    }
    std::cout << left;
    
    return 0;
}