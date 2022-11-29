#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::map<int, int> count;
    for (int i = 0; i < n; ++i) {
        int length;
        std::cin >> length;
        count[length]++;
    }

    std::vector<int> cands;
    for (auto [length, cnt] : count) {
        for (int used = 2; used <= cnt; used += 2) {
            cands.push_back(length);
        }
    }

    long long sum = 0;
    std::sort(cands.begin(), cands.end());
    while (cands.size() >= 2) {
        long long l1 = cands.back();
        cands.pop_back();
        long long l2 = cands.back();
        cands.pop_back();
        sum += l1 * l2;
    }

    std::cout << sum;

    return 0;
}