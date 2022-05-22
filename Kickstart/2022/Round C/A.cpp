#include <iostream>
#include <string>
#include <set>

void solve() {
    int n;
    std::cin >> n;
    std::string input;
    std::cin >> input;

    std::set<char> special = { '#', '@', '*', '&' };

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : input) {
        if ('A' <= ch && ch <= 'Z') {
            hasUpper = true;
        }
        if ('a' <= ch && ch <= 'z') {
            hasLower = true;
        }
        if ('0' <= ch && ch <= '9') {
            hasDigit = true;
        }
        if (special.count(ch)) {
            hasSpecial = true;
        }
    }

    if (!hasUpper) {
        input.push_back('A');
    }
    if (!hasLower) {
        input.push_back('a');
    }
    if (!hasDigit) {
        input.push_back('0');
    }
    if (!hasSpecial) {
        input.push_back('*');
    }
    while (input.size() < 7) {
        input.push_back('1');
    }

    std::cout << input << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}