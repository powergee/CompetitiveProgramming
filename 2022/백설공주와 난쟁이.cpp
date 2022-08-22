#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, c;
    std::cin >> n >> c;
    std::mt19937 rng(777);
    
    std::vector<int> color(n);
    std::vector<std::vector<int>> colorIdx(c+1);
    for (int i = 0; i < n; ++i) {
        std::cin >> color[i];
        colorIdx[color[i]].push_back(i);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--; r--;
        std::uniform_int_distribution<int> dist(l, r);
        int answer = -1;
        for (int t = 0; t < 50; ++t) {
            int testColor = color[dist(rng)];
            int testCount = std::upper_bound(colorIdx[testColor].begin(), colorIdx[testColor].end(), r) -
                            std::lower_bound(colorIdx[testColor].begin(), colorIdx[testColor].end(), l);
            if (testCount > (r-l+1)/2) {
                answer = testColor;
                break;
            }
        }

        if (answer == -1) {
            std::cout << "no\n";
        } else {
            std::cout << "yes " << answer << "\n";
        }
    }


    return 0;
}