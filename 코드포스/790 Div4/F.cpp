#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::pair<int, int> answer = {0, -1};
        std::vector<int> arr(n);
        std::map<int, int> count;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            count[arr[i]]++;
        }
        std::set<int> arrSet(arr.begin(), arr.end());
        std::vector<int> window;

        auto updateAnswer = [&]() {
            if (window.empty()) { return; }
            int l = window.front();
            int r = window.back();
            if (r-l > answer.second-answer.first) {
                answer = {l, r};
            }
        };

        for (int v : arrSet) {
            if (!window.empty() && v-window.back() > 1) {
                window.resize(0);
            }
            if (count[v] >= k) {
                window.push_back(v);
            } else {
                window.resize(0);
            }
            updateAnswer();
        }

        if (answer.first == 0) {
            printf("-1\n");
        } else {
            printf("%d %d\n", answer.first, answer.second);
        }
    }

    return 0;
}