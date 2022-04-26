#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    long long answer = 0;
    for (int c1 = 0; c1 < m; ++c1) {
        for (int c2 = c1+1; c2 < m; ++c2) {
            int count[26] = {0};
            for (int r = 0; r < n; ++r) {
                if (map[r][c1] == map[r][c2]) {
                    count[map[r][c1]-'a']++;
                }
            }
            for (int i = 0; i < 26; ++i) {
                answer += count[i]*(count[i]-1) / 2;
            }
        }
    }

    std::cout << answer;

    return 0;
}