#include <iostream>
#include <string>
#include <algorithm>

int countOverlapped(std::string& s1, std::string& s2) {
    int len = std::min(s1.size(), s2.size());
    for (int i = 0; i < len; ++i) {
        if (s1[i] != s2[i]) {
            return i;
        }
    }

    return len;
}

int main() {
    std::string before, after;
    std::cin >> before >> after;

    int o1 = countOverlapped(before, after);

    before = before.substr(o1);
    after = after.substr(o1);

    std::reverse(before.begin(), before.end());
    std::reverse(after.begin(), after.end());
    int o2 = countOverlapped(before, after);

    std::cout << (int)after.size() - o2;

    return 0;
}