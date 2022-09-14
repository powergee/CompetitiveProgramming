#include <iostream>
#include <string>
#include <map>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::string line;
    std::cin >> n >> k;
    std::getline(std::cin, line);

    std::map<std::string, int> maxDepth;
    for (int i = 0; i < k; ++i) {
        std::getline(std::cin, line);
        int bCount = 0;
        for (char ch : line) {
            if (ch == ' ') {
                bCount++;
            }
        }

        if (bCount) {
            std::string subject = line.substr(line.find_last_of(' ')+1);
            maxDepth[subject] = std::max(maxDepth[subject], bCount+1);
        } else {
            maxDepth[line] = std::max(maxDepth[line], 1);
        }
    }

    int total = 0;
    for (auto p : maxDepth) {
        total += p.second;
    }

    if (total <= n) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}