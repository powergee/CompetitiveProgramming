#include <iostream>
#include <vector>
typedef long long Long;

const int MAX = 200001;
const Long MOD = 998244353LL;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Long n, x, y;
    std::cin >> n >> x >> y;
    
    Long first = -1;
    Long single = 0;
    std::vector<int> count(MAX, 0);
    for (int i = 0; i < n; ++i) {
        Long score;
        std::cin >> score;
        count[score]++;

        if (first == -1) {
            first = score;
        } else if (first < score) {
            single += ((score - first) / x + 1) * y;
            single %= MOD;
        }
    }

    auto getLeftAnswer = [&]() -> Long {
        std::vector<Long> countSum(MAX, 0);
        for (int i = 1; i < MAX; ++i) {
            countSum[i] = countSum[i-1] + count[i];
        }

        std::vector<Long> left(MAX, 0);
        for (int i = 1; i <= x; ++i) {
            left[i] = countSum[i-1] * y;
            left[i] %= MOD;
        }
        for (int i = x+1; i < MAX; ++i) {
            left[i] = left[i-x] + count[i-x]*y + countSum[i-1]*y;
            left[i] %= MOD;
        }
        Long answer = 0;
        for (int i = 1; i < MAX; ++i) {
            answer += left[i] * count[i];
            answer %= MOD;
        }
        return answer;
    };

    std::cout << getLeftAnswer() << " " << single;

    return 0;
}