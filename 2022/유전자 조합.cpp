#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    
    std::vector<int> count(26*26, 0);
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        count[(word[0]-'A')*26 + (word[1]-'A')]++;
    }

    auto getRep = [](int hash1, int hash2) {
        int c1 = hash1/26;
        int c2 = hash2%26;
        return std::max(c1, c2);
    };

    std::vector<bool> exist(26, false);
    for (int i = 0; i < std::ssize(count); ++i) {
        if (count[i] == 0) {
            continue;
        }
        if (count[i] >= 2) {
            exist[getRep(i, i)] = true;
        }
        for (int j = i+1; j < std::ssize(count); ++j) {
            if (count[j] == 0) {
                continue;
            }
            exist[getRep(i, j)] = true;
            exist[getRep(j, i)] = true;
        }
    }

    std::cout << std::count(exist.begin(), exist.end(), true) << "\n";
    for (int i = 0; i < 26; ++i) {
        if (exist[i]) {
            std::cout << char('A'+i) << " ";
        }
    }

    return 0;
}