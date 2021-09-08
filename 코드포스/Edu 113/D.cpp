#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        std::vector<int> verStreet(n), horStreet(m);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &verStreet[i]);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d", &horStreet[i]);
        }

        std::vector<std::pair<int, int>> points(k);
        for (int i = 0; i < k; ++i) {
            scanf("%d %d", &points[i].first, &points[i].second);
        }

        long long result = 0;
        std::vector<std::vector<int>> verBetween(n);
        for (int i = 0; i < k; ++i) {
            int x = points[i].first;
            auto found = std::lower_bound(verStreet.begin(), verStreet.end(), x);
            if (*found != x) {
                verBetween[found-verStreet.begin()].push_back(i);
            }
        }

        for (int i = 0; i < n; ++i) {
            std::map<int, int> count;
            for (auto p : verBetween[i]) {
                count[points[p].second]++;
            }
            int sum = 0;
            for (auto p : count) {
                result += sum * p.second;
                sum += p.second;
            }
        }

        std::vector<std::vector<int>> horBetween(m);
        for (int i = 0; i < k; ++i) {
            int y = points[i].second;
            auto found = std::lower_bound(horStreet.begin(), horStreet.end(), y);
            if (*found != y) {
                horBetween[found-horStreet.begin()].push_back(i);
            }
        }

        for (int i = 0; i < m; ++i) {
            std::map<int, int> count;
            for (auto p : horBetween[i]) {
                count[points[p].first]++;
            }
            int sum = 0;
            for (auto p : count) {
                result += sum * p.second;
                sum += p.second;
            }
        }

        printf("%lld\n", result);
    }

    return 0;
}