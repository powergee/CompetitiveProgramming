#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, std::string>> players;
    std::vector<int> count(n+1, 0);

    int classNum;
    std::string name;
    while ((std::cin >> classNum >> name), (classNum != 0 && name != "0")) {
        if (count[classNum] < m) {
            ++count[classNum];
            players.emplace_back(classNum, name);
        }
    }

    std::sort(players.begin(), players.end(), [](auto p1, auto p2) -> bool {
        int r1 = p1.first % 2;
        int r2 = p2.first % 2;
        if (r1 != r2) {
            return r1 > r2;
        } else if (p1.first != p2.first) {
            return p1.first < p2.first;
        } else if (p1.second.size() != p2.second.size()) {
            return p1.second.size() < p2.second.size();
        }
        return p1.second < p2.second;
    });

    for (auto p : players) {
        std::cout << p.first << " " << p.second << "\n";
    }

    return 0;
}