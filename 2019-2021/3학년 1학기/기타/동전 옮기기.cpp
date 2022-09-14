#include <iostream>
#include <algorithm>

int n, c1, c2;
std::string origin, target;
std::string base;
char pivot[2];
int dp[10000][3];

bool isPossible(int start, int step) {
    if (start == (int)target.size()) {
        if (step == 2) {
            return true;
        } else {
            return false;
        }
    }

    int& result = dp[start][step];
    if (result != -1) {
        return result == 1;
    }

    result = 0;
    if (target[start] == base[start-step] && isPossible(start+1, step)) {
        result = 1;
    }
    if (step < 2 && target[start] == pivot[step] && isPossible(start+1, step+1)) {
        result = 1;
    }

    return result == 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> origin >> target >> c1 >> c2;
    base = origin.substr(0, c1) + origin.substr(c1+1, c2-c1-1) + origin.substr(c2+1);
    pivot[0] = origin[c1];
    pivot[1] = origin[c2];

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    std::cout << (isPossible(0, 0) ? "YES" : "NO");

    return 0;
}