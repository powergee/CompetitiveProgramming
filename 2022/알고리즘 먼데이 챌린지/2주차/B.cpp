#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;

    int answer = 1;
    for (int i = 1; i < n; ++i) {
        if (str[i-1] != str[i]) {
            answer++;
        }
    }
    std::cout << answer;

    return 0;
}