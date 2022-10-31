#include <iostream>
#include <string>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int balance, q;
    std::queue<int> waiting;
    std::cin >> balance >> q;

    while (q--) {
        std::string kind;
        int arg;
        std::cin >> kind >> arg;
        
        if (kind == "deposit") {
            balance += arg;
        } else if (kind == "pay") {
            if (balance >= arg) {
                balance -= arg;
            }
        } else {
            if (waiting.size() || balance < arg) {
                waiting.push(arg);
            } else {
                balance -= arg;
            }
        }

        while (waiting.size() && waiting.front() <= balance) {
            balance -= waiting.front();
            waiting.pop();
        }
    }

    std::cout << balance;

    return 0;
}