#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> curr(n), prev(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> curr[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> prev[i];
    }

    int answer = 0;
    for (int i = 0; i < n || i < m; ++i) {
        if (i < n && i < m) {
            answer = std::max(answer, prev[i]-curr[i]);
        } else if (i < n) {
            break;
        } else {
            answer = std::max(answer, prev[i]);
        }
    }

    std::cout << answer;
    
    return 0;
}