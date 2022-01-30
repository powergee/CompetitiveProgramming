#include <iostream>
#include <stack>

char str[500001];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", str);

    int mid = 0;
    std::stack<int> left, right;
    for (int i = 0; i < n; ++i) {
        if (str[i] == 'L') {
            right.push(mid);
        } else {
            left.push(mid);
        }
        mid++;
    }
    right.push(mid);
    while (!left.empty()) {
        right.push(left.top());
        left.pop();
    }

    while (!right.empty()) {
        printf("%d ", right.top());
        right.pop();
    }

    return 0;
}