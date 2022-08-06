#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int query(int a, int b) {
    std::cout << "? " << a << " " << b << "\n";
    std::cout.flush();
    int res;
    std::cin >> res;
    return res;
}

void answer(int a) {
    std::cout << "! " << a << "\n";
    std::cout.flush();
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::vector<int> cands(1<<n);
        std::iota(cands.begin(), cands.end(), 1);
        while (cands.size() > 1) {
            if (cands.size() == 2) {
                int res = query(cands[0], cands[1]);
                if (res == 0) {
                    return 1;
                } else if (res == 1) {
                    cands = { cands[0] };
                } else {
                    cands = { cands[1] };
                }
            } else {
                std::vector<int> winners(cands.size()/4);
                for (int i = 0; i < cands.size(); i += 4) {
                    int a = cands[i];
                    int b = cands[i+1];
                    int c = cands[i+2];
                    int d = cands[i+3];

                    int first = query(a, c);
                    int x, y;
                    if (first == 0) { // a, c are losers
                        x = b;
                        y = d;
                    } else if (first == 1) { // b, c are losers
                        x = a;
                        y = d;
                    } else { // a, d are losers
                        x = b;
                        y = c;
                    }

                    int second = query(x, y);
                    if (second == 0) { // Unexpected
                        return -1;
                    } else if (second == 1) {
                        winners[i/4] = x;
                    } else {
                        winners[i/4] = y;
                    }
                }
                cands = winners;
            }
        }

        answer(cands[0]);
    }

    return 0;
}