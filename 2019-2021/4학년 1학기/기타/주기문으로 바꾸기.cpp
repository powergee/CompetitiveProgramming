#include <iostream>
#include <string>
#include <map>
#include <vector>

int main() {
    int m;
    std::cin >> m;
    std::string s;
    std::cin >> s;
    int n = s.size();

    int answer = INT32_MAX;
    for (int width = 1; width <= m; ++width) {
        std::vector<std::map<char, int>> countPerLine(width);
        for (int i = 0; i < n; ++i) {
            countPerLine[i%width][s[i]]++;
        }
        int changed = 0;
        for (int i = 0; i < width; ++i) {
            int total = 0;
            int max = 0;
            for (auto [ch, cnt] : countPerLine[i]) {
                total += cnt;
                max = std::max(max, cnt);
            }
            changed += total - max;
        }
        answer = std::min(answer, changed);
    }

    std::cout << answer;

    return 0;
}