#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    std::vector<std::vector<int>> height(n, std::vector<int>(m, 0));
    for (int j = 0; j < m; ++j) {
        height[0][j] = (map[0][j] == '.');
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            height[i][j] = (map[i][j] == '.' ? height[i-1][j]+1 : 0);
        }
    }

    std::vector<int> maxWidth(n+1, 0);
    for (int i = 0; i < n; ++i) {
        std::stack<std::pair<int, int>> st;

        auto popStack = [&](int currCol) {
            auto prev = st.top();
            st.pop();
            int height = prev.first;
            int width = (st.empty() ? currCol : currCol - st.top().second - 1);
            maxWidth[height] = std::max(maxWidth[height], width);
        };

        st.emplace(height[i][0], 0);
        for (int j = 1; j < m; ++j) {
            while (!st.empty() && height[i][j] < st.top().first) {
                popStack(j);
            }
            st.emplace(height[i][j], j);
        }
        while (!st.empty()) {
            popStack(m);
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int a, b;
        std::cin >> a >> b;
        if (b <= maxWidth[a]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}