#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::string str;
        std::cin >> str;

        int segStart = 0, answer = 0;
        for (int i = 0; i+1 < n; ++i) {
            if (str[i] != str[i+1]) {
                if ((i-segStart+1) % 2 == 0) {
                    segStart = i+1;
                } else {
                    str[i] = str[i+1];
                    segStart = i;
                    ++answer;
                }
            }
        }
        if ((n-segStart) % 2 == 1) {
            ++answer;
        }
        std::cout << answer << "\n";
    }

    return 0;
}