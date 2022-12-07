#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::tuple<std::string, int, int>> problem(n);
    for (int i = 0; i < n; ++i) {
        std::string name;
        int num, diff;
        std::cin >> name >> num >> diff;
        problem[i] = { name, num, diff };
    }

    std::sort(problem.begin(), problem.end(), [](auto t1, auto t2) {
        return std::get<1>(t1) < std::get<1>(t2);
    });

    for (auto [name, _, diff] : problem) {
        char ch = name[diff-1];
        if ('a' <= ch && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
        std::cout << ch;
    }

    return 0;
}