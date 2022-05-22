#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <tuple>
#define LEFT 0
#define RIGHT 1

using Ant = std::tuple<int, int, int>;

void solve() {
    int n, l;
    std::cin >> n >> l;
    
    std::vector<Ant> position(n);
    for (int i = 0; i < n; ++i) {
        int p, d;
        std::cin >> p >> d;
        position[i] = { p, d, i };
    }
    std::sort(position.begin(), position.end());

    std::vector<std::pair<int, int>> timestamps;
    timestamps.reserve(n);
    std::deque<int> prev;
    std::vector<int> posVec;
    for (auto [p, d, i] : position) {
        if (d == LEFT) {
            if (prev.empty()) {
                timestamps.emplace_back(p, i);
                continue;
            }
            int pi = prev.front();
            prev.pop_front();
            timestamps.emplace_back(p, pi);
            prev.push_back(i);
        } else {
            prev.emplace_back(i);
            posVec.push_back(p);
        }
    }

    while (!prev.empty()) {
        int i = prev.back();
        prev.pop_back();
        timestamps.emplace_back(l-posVec[prev.size()], i);
    }

    std::sort(timestamps.begin(), timestamps.end());
    for (auto [t, i] : timestamps) {
        std::cout << i+1 << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}