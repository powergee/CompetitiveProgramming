#include <iostream>
#include <stack>

typedef long long Long;

int main() {
    Long n;
    scanf("%lld", &n);

    std::stack<char> solution;
    while (n > 0) {
        if (n % 2 == 0) {
            solution.push('B');
            n /= 2;
        } else {
            solution.push('A');
            n--;
        }
    }
    while (!solution.empty()) {
        putchar(solution.top());
        solution.pop();
    }

    return 0;
}