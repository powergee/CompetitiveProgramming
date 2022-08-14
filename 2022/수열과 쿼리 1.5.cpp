#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class SqrtCounter {
private:
    const int MAX = 10000;
    const int SQRT = int(std::sqrt(MAX+1)) + 1;
    std::vector<int> count, groupBase;

public:
    SqrtCounter() : count(MAX+1, 0), groupBase(SQRT+1, 0) {}
    
    void add(int val, int coeff) {
        for (int i = 0; i < val/SQRT; ++i) {
            groupBase[i] += coeff;
        }
        for (int i = val/SQRT*SQRT; i < val; ++i) {
            count[i] += coeff;
        }
    }

    int countBigger(int k) {
        return groupBase[k/SQRT]+count[k];
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    const int SQRT = int(std::sqrt(n)) + 1;
    std::vector<SqrtCounter> counter(n/SQRT+1);
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        counter[i/SQRT].add(arr[i], 1);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int i, v;
            std::cin >> i >> v;
            i--;
            counter[i/SQRT].add(arr[i], -1);
            counter[i/SQRT].add((arr[i] = v), 1);
        } else {
            int i, j, k;
            std::cin >> i >> j >> k;
            i--; j--;
            int g1 = i/SQRT;
            int g2 = j/SQRT;
            int answer = 0;
            if (g1 == g2) {
                for (int idx = i; idx <= j; ++idx) {
                    if (arr[idx] > k) {
                        answer++;
                    }
                }
            } else {
                for (int idx = i; idx < (g1+1)*SQRT; ++idx) {
                    if (arr[idx] > k) {
                        answer++;
                    }
                }
                for (int idx = j; idx >= g2*SQRT; --idx) {
                    if (arr[idx] > k) {
                        answer++;
                    }
                }
                for (int idx = g1+1; idx <= g2-1; ++idx) {
                    answer += counter[idx].countBigger(k);
                }
            }
            std::cout << answer << "\n";
        }
    }

    return 0;
}