#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> map(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> map[i];
    }

    std::vector<int> dp(h*w*h*w, -1);
    std::function<int(int, int, int, int)> getGrundy = [&](int pr, int pc, int qr, int qc) -> int {
        if (pr > qr || pc > qc) {
            return 0;
        }
        int& result = dp[w*h*w*pr + h*w*pc + w*qr + qc];
        if (result != -1) {
            return result;
        }
        
        std::vector<bool> foundGrundy(100, false);
        for (int r = pr; r <= qr; ++r) {
            for (int c = pc; c <= qc; ++c) {
                if (map[r][c] == '.') {
                    int grundy = 0;
                    grundy ^= getGrundy(pr, pc, r-1, c-1);
                    grundy ^= getGrundy(pr, c+1, r-1, qc);
                    grundy ^= getGrundy(r+1, pc, qr, c-1);
                    grundy ^= getGrundy(r+1, c+1, qr, qc);
                    foundGrundy[grundy] = true;
                }
            }
        }

        for (int i = 0; i < foundGrundy.size(); ++i) {
            if (!foundGrundy[i]) {
                return result = i;
            }
        }
        return 0;
    };

    if (getGrundy(0, 0, h-1, w-1) > 0) {
        std::cout << "First";
    } else {
        std::cout << "Second";
    }

    return 0;
}