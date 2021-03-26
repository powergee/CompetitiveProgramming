#include <iostream>
#include <string>
#include <algorithm>

int getMaxLength(std::string& a, std::string& b, int aStart, int bStart) {
    int length = 0;
    while (aStart + length < (int)a.size() && bStart + length < (int)b.size()) {
        if (a[aStart+length] == b[bStart+length]) {
            ++length;
        } else {
            break;
        }
    }
    return length;
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        std::string a, b;
        std::cin >> a >> b;

        int same = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = 0; j < (int)b.size(); ++j) {
                same = std::max(same, getMaxLength(a, b, i, j));
            }
        }

        std::cout << a.size() + b.size() - same*2 << '\n';
    }
}