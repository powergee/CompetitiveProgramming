#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::map<int, int> total;

    for (int i = 0; i < m; ++i) {
        int count;
        std::cin >> count;

        while (count--) {
            int executed;
            std::cin >> executed;
            total[executed]++;
        }
    }

    std::vector<std::pair<int, int>> totalVec(total.begin(), total.end());
    std::sort(totalVec.begin(), totalVec.end(), [](auto p1, auto p2) {
        if (p1.second != p2.second) {
            return p1.second > p2.second;
        }
        return p1.first > p2.first;
    });
    
    for (int i = 0; i < totalVec.size(); ++i) {
        if (i > 0 && totalVec[i-1].second != totalVec[i].second) {
            break;
        }
        std::cout << totalVec[i].first << " ";
    }

    return 0;
}