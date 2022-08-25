#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::string str;
        std::cin >> str;
        
        int i, isPalin = 0;
        for (i = 0; ; ++i) {
            int j = int(str.size())-1-i;
            if (i >= j) {
                isPalin = true;
                break;
            } else if (str[i] != str[j]) {
                break;
            }
        }

        std::cout << isPalin << " " << i+1 << "\n";
    }

    return 0;
}