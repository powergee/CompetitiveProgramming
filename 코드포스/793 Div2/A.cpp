#include <iostream>
#include <string>

void solve() {
    int n;
    std::cin >> n;
    std::string str;
    std::cin >> str;

    char mid = str[n/2];
    int count = 0;
    for (int i = n/2; i < n; ++i) {
        if (str[i] == mid) {
            count++;
        } else {
            break;
        }
    }
    for (int i = n/2-1; i >= 0; --i) {
        if (str[i] == mid) {
            count++;
        } else {
            break;
        }
    }

    std::cout << count << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}