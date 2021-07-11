#include <iostream>
#include <string>
#include <set>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::multiset<char>> indexer(m);

        for (int i = 0; i < n; ++i) {
            std::string line;
            std::cin >> line;
            for (int j = 0; j < m; ++j) {
                indexer[j].insert(line[j]);
            }
        }
        for (int i = 0; i < n-1; ++i) {
            std::string line;
            std::cin >> line;
            for (int j = 0; j < m; ++j) {
                auto found = indexer[j].find(line[j]);
                indexer[j].erase(found);
            }
        }
        for (int i = 0; i < m; ++i) {
            char ch = *indexer[i].begin();
            std::cout << ch;
        }
        std::cout << "\n";
        std::cout.flush();
    }

    return 0;
}