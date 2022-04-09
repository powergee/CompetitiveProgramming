#include <iostream>
#include <string>

void solve() {
    std::string input;
    std::cin >> input;

    for (int i = 0; i < input.size();) {
        std::string next = input.substr(0, i) + input[i] + input[i] + input.substr(i+1);
        if (next < input) {
            input = next;
            i += 2;
        } else {
            ++i;
        }
    }

    std::cout << input << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}