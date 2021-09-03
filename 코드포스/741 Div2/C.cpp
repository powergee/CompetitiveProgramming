#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::string binStr;
        std::cin >> binStr;

        bool printed = false;
        for (int i = n/2; i < n; ++i) {
            if (binStr[i] == '0') {
                printf("%d %d %d %d\n", 1, i+1, 1, i);
                printed = true;
                break;
            }
        }
        if (printed) {
            continue;
        }

        for (int i = n-n/2-1; i >= 0; --i) {
            if (binStr[i] == '0') {
                printf("%d %d %d %d\n", i+1, n, i+2, n);
                printed = true;
                break;
            }
        }
        if (printed) {
            continue;
        }

        printf("%d %d %d %d\n", 1, n/2, n-n/2+1, n);
    }
}