#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::string bin;
        std::cin >> bin;

        int one = 0, zero = 0;
        for (int i = 0; i < bin.size(); ++i) {
            (bin[i] == '1' ? one : zero)++;
        }

        if (one != zero) {
            printf("%d\n", std::min(one, zero));
        } else if (bin.back() == '1') {
            printf("%d\n", one-1);
        } else {
            printf("%d\n", zero-1);
        }
    }

    return 0;
}