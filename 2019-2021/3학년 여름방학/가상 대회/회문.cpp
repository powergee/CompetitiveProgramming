#include <iostream>
#include <algorithm>
#include <string>

std::pair<int, int> notMatched;

bool isPalin(std::string word) {
    int n = word.size();
    for (int i = 0; i < n; ++i) {
        if (word[i] != word[n-1-i]) {
            notMatched = {i, n-1-i};
            return false;
        }
    }
    return true;
}

std::string subStringWithRange(std::string word, int left, int right) {
    return word.substr(left, right-left+1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        std::string word;
        std::cin >> word;

        if (isPalin(word)) {
            printf("0\n");
        } else {
            int left = std::min(notMatched.first, notMatched.second);
            int right = std::max(notMatched.first, notMatched.second);
            if (isPalin(subStringWithRange(word, left+1, right)) || isPalin(subStringWithRange(word, left, right-1))) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        }
    }

    return 0;
}