#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>

int main() {
    int n;
    std::string line;
    std::cin >> n >> line;

    std::vector<int> pos[26];
    for (int i = 0; i < n; ++i) {
        pos[line[i]-'a'].push_back(i);
    }

    for (int i = 0, j = n-1; i < n; ++i) {
        bool found = false;
        for (int a = 0; a < line[i]-'a' && !found; ++a) {
            while (!pos[a].empty() && j < pos[a].back()) {
                pos[a].pop_back();
            }

            if (!pos[a].empty() && i < pos[a].back()) {
                found = true;
                j = pos[a].back()-1;
                std::swap(line[i], line[pos[a].back()]);
                pos[a].pop_back();
            }
        }
    }

    std::cout << line;

    return 0;
}