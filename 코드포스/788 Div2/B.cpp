#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        
        std::string line;
        std::cin >> line;
        int k;
        std::cin >> k;
        bool special[26] = { false, };
        for (int i = 0; i < k; ++i) {
            std::string spline;
            std::cin >> spline;
            special[spline[0]-'a'] = true;
        }

        int left = 0, maxLength = 0;
        for (int i = 0; i < n; ++i) {
            if (special[line[i]-'a']) {
                maxLength = std::max(maxLength, i-left);
                left = i;
            }
        }
        std::cout << maxLength << "\n";
    }

    return 0;
}