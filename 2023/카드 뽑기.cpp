#include <iostream>
#include <map>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::map<int, int> count;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        count[v]++;
    }
    
    long long answer = 1;
    for (auto [v, cnt] : count) {
        answer *= (cnt+1);
        answer %= 1000000007;
    }
    std::cout << answer - 1;

    return 0;
}