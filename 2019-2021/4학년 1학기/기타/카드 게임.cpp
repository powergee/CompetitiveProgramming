#include <iostream>
#include <vector>
#include <functional>
#include <stack>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<bool> exist(n+1, false);
    std::vector<int> next(n+1);

    for (int i = 0; i < m; ++i) {
        int chosen;
        std::cin >> chosen;
        exist[chosen] = true;
    }
    for (int i = 0; i <= n-1; ++i) {
        next[i] = i+1;
    }

    auto findTarget = [&](int start) -> int {
        std::stack<int> callStack;
        callStack.push(start);

        while (!exist[callStack.top()]) {
            callStack.push(next[callStack.top()]);
        }
        int result = callStack.top();
        exist[result] = false;
        callStack.pop();
        while (!callStack.empty()) {
            next[callStack.top()] = result+1;
            callStack.pop();
        }
        return result;
    };

    for (int i = 0; i < k; ++i) {
        int q;
        std::cin >> q;
        std::cout << findTarget(q+1) << "\n";
    }

    return 0;
}