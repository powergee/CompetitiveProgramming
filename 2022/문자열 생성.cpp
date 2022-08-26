#include <iostream>
#include <string>
#include <functional>

void print(char ch) {
    static int printed = 0;
    std::cout << ch;
    printed++;
    if (printed % 80 == 0) {
        std::cout << "\n";
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::string str;
    str.reserve(n+1);

    for (int i = 0; i < n; ++i) {
        char ch;
        std::cin >> ch;
        str += ch;
    }

    int l = 0, r = n-1;
    while (l <= r) {
        if (str[l] < str[r]) {
            print(str[l++]);
        } else if (str[l] > str[r]) {
            print(str[r--]);
        } else {
            int d = 0;
            while (l+d < r-d && str[l+d] == str[r-d]) {
                ++d;
            }
            if (str[l+d] < str[r-d]) {
                print(str[l++]);
            } else {
                print(str[r--]);
            }
        }
    }

    return 0;
}