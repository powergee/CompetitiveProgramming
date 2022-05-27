#include <iostream>
#include <string>
#include <map>

std::map<char, int> countChars(std::string s) {
    std::map<char, int> count;
    for (char ch : s) {
        count[ch]++;
    }
    return count;
}

std::string removeVowels(std::string s) {
    static const std::string VOWELS = "aeiou";
    std::string result;
    for (char ch : s) {
        if (VOWELS.find(ch) == VOWELS.npos) {
            result += ch;
        }
    }
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;

    if (countChars(a) != countChars(b)) {
        std::cout << "NO\n";
    } else if (a.front() != b.front() || a.back() != b.back()) {
        std::cout << "NO\n";
    } else if (removeVowels(a) != removeVowels(b)) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }

    return 0;
}