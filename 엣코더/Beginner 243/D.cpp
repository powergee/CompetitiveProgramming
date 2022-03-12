#include <iostream>
#include <vector>
#include <string>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Long n, x;
    std::cin >> n >> x;

    std::string line;
    std::cin >> line;
    std::vector<char> stack;
    for (char ch : line) {
        switch (ch)
        {
        case 'U':
            if (stack.empty()) {
                x /= 2;
            } else {
                stack.pop_back();
            }
            break;
        default:
            stack.push_back(ch);
            break;
        }
    }

    for (char ch : stack) {
        if (ch == 'L') {
            x = x*2;
        } else {
            x = x*2+1;
        }
    }

    printf("%lld", x);

    return 0;
}