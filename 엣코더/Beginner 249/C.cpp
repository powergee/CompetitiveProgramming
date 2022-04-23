#include <iostream>
#include <string>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::string> strs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> strs[i];
    }

    int answer = 0;
    for (int mask = 1; mask < (1<<n); ++mask) {
        int count[26] = {0};
        for (int i = 0; i < n; ++i) {
            if (mask & (1<<i)) {
                for (char ch : strs[i]) {
                    count[ch-'a']++;
                }
            }
        }
        int curr = 0;
        for (int i = 0; i < 26; ++i) {
            if (count[i] == k) {
                ++curr;
            }
        }
        answer = std::max(answer, curr);
    }

    std::cout << answer;

    return 0;
}