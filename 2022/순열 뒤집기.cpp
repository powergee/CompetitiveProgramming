#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> rangeSt;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        rangeSt.emplace_back(v, v);
        while (rangeSt.size() >= 2) {
            auto p2 = rangeSt[rangeSt.size()-2];
            auto p1 = rangeSt[rangeSt.size()-1];
            if (p2.second+1 == p1.first) {
                rangeSt.pop_back();
                rangeSt.pop_back();
                rangeSt.emplace_back(p2.first, p1.second);
            } else if (p1.second+1 == p2.first) {
                rangeSt.pop_back();
                rangeSt.pop_back();
                rangeSt.emplace_back(p1.first, p2.second);
            } else {
                break;
            }
        }
    }

    if (rangeSt.size() == 1) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}