#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

typedef long long Long;
using Board = std::vector<std::vector<Long>>;

int main() {
    int n;
    scanf("%d", &n);

    Board board(n, std::vector<Long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%lld", &board[i][j]);
        }
    }

    Long maxValue = 0;
    std::function<void(Board, int)> iterateCases = [&](Board curr, int moved) {
        if (moved == 5) {
            for (auto row : curr) {
                for (auto val : row) {
                    maxValue = std::max(maxValue, val);
                }
            }
            return;
        }

        { // LEFT
            Board next(n, std::vector<Long>(n, 0));
            for (int i = 0; i < n; ++i) {
                std::vector<Long> stack;
                for (int j = 0; j < n; ++j) {
                    if (curr[i][j] == 0) {
                        continue;
                    } else if (!stack.empty() && stack.back() == curr[i][j]) {
                        stack.back() *= 2;
                        stack.back() += 1;
                    } else {
                        stack.push_back(curr[i][j]);
                    }
                }
                for (int j = 0; j < stack.size(); ++j) {
                    next[i][j] = stack[j]/2*2;
                }
            }
            iterateCases(next, moved+1);
        }
        { // RIGHT
            Board next(n, std::vector<Long>(n, 0));
            for (int i = 0; i < n; ++i) {
                std::vector<Long> stack;
                for (int j = n-1; j >= 0; --j) {
                    if (curr[i][j] == 0) {
                        continue;
                    } else if (!stack.empty() && stack.back() == curr[i][j]) {
                        stack.back() *= 2;
                        stack.back() += 1;
                    } else {
                        stack.push_back(curr[i][j]);
                    }
                }
                for (int j = 0; j < stack.size(); ++j) {
                    next[i][n-1-j] = stack[j]/2*2;
                }
            }
            iterateCases(next, moved+1);
        }
        { // UP
            Board next(n, std::vector<Long>(n, 0));
            for (int j = 0; j < n; ++j) {
                std::vector<Long> stack;
                for (int i = 0; i < n; ++i) {
                    if (curr[i][j] == 0) {
                        continue;
                    } else if (!stack.empty() && stack.back() == curr[i][j]) {
                        stack.back() *= 2;
                        stack.back() += 1;
                    } else {
                        stack.push_back(curr[i][j]);
                    }
                }
                for (int i = 0; i < stack.size(); ++i) {
                    next[i][j] = stack[i]/2*2;
                }
            }
            iterateCases(next, moved+1);
        }
        { // DOWN
            Board next(n, std::vector<Long>(n, 0));
            for (int j = 0; j < n; ++j) {
                std::vector<Long> stack;
                for (int i = n-1; i >= 0; --i) {
                    if (curr[i][j] == 0) {
                        continue;
                    } else if (!stack.empty() && stack.back() == curr[i][j]) {
                        stack.back() *= 2;
                        stack.back() += 1;
                    } else {
                        stack.push_back(curr[i][j]);
                    }
                }
                for (int i = 0; i < stack.size(); ++i) {
                    next[n-1-i][j] = stack[i]/2*2;
                }
            }
            iterateCases(next, moved+1);
        }
    };
    iterateCases(board, 0);
    printf("%lld", maxValue);

    return 0;
}