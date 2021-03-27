#include <iostream>
#include <stack>

int main() {
    int k;
    scanf("%d", &k);

    std::stack<int> exp;
    for (int i = 0; i < k; ++i) {
        int comm;
        scanf("%d", &comm);
        if (comm == 0) {
            exp.pop();
        } else {
            exp.push(comm);
        }
    }

    int sum = 0;
    while (!exp.empty()) {
        int val = exp.top();
        exp.pop();
        sum += val;
    }

    printf("%d", sum);

    return 0;
}