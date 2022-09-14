#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);;

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        int n;
        std::string str;
        std::cin >> n >> str;
        std::vector<long long> dist(n, INT32_MAX);
        long long leftOne = str.find_first_of('1');
        long long rightOne = str.find_last_of('1');

        for (int i = leftOne; i < n; ++i) {
            if (str[i] == '1') {
                leftOne = i;
            }
            dist[i] = std::min(dist[i], i-leftOne);
        }
        for (int i = rightOne; i >= 0; --i) {
            if (str[i] == '1') {
                rightOne = i;
            }
            dist[i] = std::min(dist[i], rightOne-i);
        }

        printf("%lld\n", std::accumulate(dist.begin(), dist.end(), 0LL));
    }

    return 0;
}