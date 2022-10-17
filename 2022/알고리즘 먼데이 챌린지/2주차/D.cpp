#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    int answer = 0;
    auto add = [&](int r, int c) {
        if (1 <= r && r <= n && 1 <= c && c <= n) {
            answer++;
        }
    };

    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        add(a, b);
        add(a+1, b);
        add(a-1, b);
        add(a, b+1);
        add(a, b-1);
    }

    std::cout << answer;

    return 0;
}