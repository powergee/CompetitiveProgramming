#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    std::map<int, int> count;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        count[arr[i]]++;
    }

    if (n == 1) {
        std::cout << 1 << "\n";
        return;
    }
    
    std::vector<std::pair<int, int>> countVec(count.begin(), count.end());
    int multiple = 0, single = 0, extra = 0;
    for (int i = 0; i < countVec.size(); ++i) {
        auto [v, cnt] = countVec[i];
        if (cnt == 1) {
            ++single;
        } else {
            ++multiple;
        }
    }

    std::cout << single / 2 + (single % 2) + multiple << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}