#include <iostream>
#include <vector>
#include <bits/stdc++.h>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<Long> matrix(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> matrix[i];
    }

    int top = 0;
    for (int e = 59; e >= 0; --e) {
        bool found = false;
        for (int i = top; i < n; ++i) {
            if (matrix[i]&(1LL<<e)) {
                std::swap(matrix[i], matrix[top]);
                found = true;
            }
        }

        if (found) {
            for (int i = 0; i < n; ++i) {
                if (i == top) {
                    continue;
                } else if (matrix[i]&(1LL<<e)) {
                    matrix[i] ^= matrix[top];
                }
            }
            top++;
        }
    }

    Long answer = 0;
    for (int i = 0; i < n; ++i) {
        answer ^= matrix[i];
    }
    std::cout << answer << "\n";

    return 0;
}