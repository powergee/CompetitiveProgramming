#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::string str;
        std::cin >> n >> str;

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            int count[10] = {};
            int maxCount = 0, kinds = 0;
            for (int j = i; j < n; ++j) {
                count[str[j]-'0']++;
                maxCount = std::max(maxCount, count[str[j]-'0']);
                kinds += count[str[j]-'0'] == 1 ? 1 : 0;
                if (maxCount <= kinds) {
                    ++answer;
                }
            }
        }

        std::cout << answer << "\n";
    }

    return 0;
}