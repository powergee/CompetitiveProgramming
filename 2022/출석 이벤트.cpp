#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, p;
    std::cin >> n >> p;

    std::vector<int> cands { p };
    if (n >= 5) {
        cands.push_back(p-500);
    }
    if (n >= 10) {
        cands.push_back(p/10*9);
    }
    if (n >= 15) {
        cands.push_back(p-2000);
    }
    if (n >= 20) {
        cands.push_back(p/4*3);
    }

    int min = *std::min_element(cands.begin(), cands.end());
    std::cout << std::max(min, 0);

    return 0;
}