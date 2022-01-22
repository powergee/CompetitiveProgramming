#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>

bool isPalindrome(const std::string& str, int idx = 0) {
    if (str[idx] != str[int(str.size())-1-idx]) {
        return false;
    }
    if (int(str.size())/2 == idx) {
        return true;
    }
    return isPalindrome(str, idx+1);
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::vector<std::string> words, reversed;

        bool answer = false;
        for (int i = 0; i < n; ++i) {
            std::string word;
            std::cin >> word;
            if (isPalindrome(word)) {
                answer = true;
            }
            if (word.size() > 1) {
                words.push_back(word);
                std::reverse(word.begin(), word.end());
                reversed.push_back(word);
            }
        }

        std::set<std::string> prev;
        for (int i = 0; i < words.size(); ++i) {
            answer = answer || prev.find(reversed[i]) != prev.end();
            if (words[i].size() == 2) {
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    answer = answer || prev.find(reversed[i] + ch) != prev.end();
                }
            }
            prev.insert(words[i]);
        }

        prev.clear();
        for (int i = int(words.size())-1; i >= 0; --i) {
            answer = answer || prev.find(reversed[i]) != prev.end();
            if (words[i].size() == 2) {
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    answer = answer || prev.find(std::string() + ch + reversed[i]) != prev.end();
                }
            }
            prev.insert(words[i]);
        }

        std::cout << (answer ? "YES\n" : "NO\n");
    }

    return 0;
}