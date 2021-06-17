#include <iostream>
#include <string>
#include <map>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::map<char, int> charMap;
    std::vector<std::string> words;
    std::vector<int> bitmasks;

    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        words.push_back(word);
        for (char ch : word) {
            if (charMap.find(ch) == charMap.end()) {
                charMap[ch] = (int)charMap.size();
            }
        }
    }

    for (std::string word : words) {
        int mask = 0;
        for (char ch : word) {
            mask |= (1 << charMap[ch]);
        }
        bitmasks.push_back(mask);
    }

    int answer = 0;
    for (int v = 0; v < (1<<charMap.size()); ++v) {
        if (__builtin_popcount(v) == std::min(k, (int)charMap.size())) {
            int curr = 0;
            for (int mask : bitmasks) {
                curr += ((mask & v) == mask ? 1 : 0);
            }
            answer = std::max(answer, curr);
        }
    }
    std::cout << answer;

    return 0;
}