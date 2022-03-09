#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        std::string src, dst;
        std::cin >> src >> dst;

        bool possible = false;
        for (int i = 0; i < src.size(); i += 2) {
            if (dst[0] == src[i]) {
                possible = true;
            }
        }
        std::cout << (possible ? "YES" : "NO") << "\n";
    }

    return 0;
}