#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, en = 0, on = 0;
        scanf("%d", &n);
        std::vector<int> even, odd;

        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (val % 2 == 1) {
                odd.push_back(val);
                ++on;
            } else {
                even.push_back(val);
                ++en;
            }
        }

        long long answer = on * en + (en * (en-1) / 2);
        for (int i = 0; i < odd.size(); ++i) {
            for (int j = i+1; j < odd.size(); ++j) {
                if (std::gcd(odd[i], odd[j]) > 1) {
                    ++answer;
                }
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}