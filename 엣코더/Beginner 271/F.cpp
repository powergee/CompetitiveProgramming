#include <iostream>
#include <map>

typedef long long Long;

int main() {
    int n;
    std::cin >> n;

    int map[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> map[i][j];
        }
    }

    std::map<Long, Long> middleSums[n][n];
    for (int move = 0; move < (1<<(n-1)); ++move) {
        int r = 0, c = 0;
        int sum = map[0][0];
        for (int i = 0; i < n-1; ++i) {
            if (move&(1<<i)) {
                r++;
            } else {
                c++;
            }
            sum ^= map[r][c];
        }
        middleSums[r][c][sum]++;
    }

    for (int move = 0; move < (1<<(n-2)); ++move) {
        int r = n-1, c = n-1;
        int sum = map[n-1][n-1];
        for (int i = 0; i < n-2; ++i) {
            if (move&(1<<i)) {
                r--;
            } else {
                c--;
            }
            sum ^= map[r][c];
        }
        middleSums[r][c][sum]++;
    }

    Long answer = 0;
    for (int i = 0; i < n; ++i) {
        int j = n-1-i;
        for (auto [sum, cnt] : middleSums[i][j]) {
            if (i+1 < n) {
                answer += cnt * middleSums[i+1][j][sum];
            }
            if (j+1 < n) {
                answer += cnt * middleSums[i][j+1][sum];
            }
        }
    }

    std::cout << answer;

    return 0;
}