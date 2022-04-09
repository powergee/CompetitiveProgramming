#include <iostream>
#include <string>
#include <set>
#include <numeric>
#define MAX 1000000000LL

typedef long long Long;

void solve() {
    int n;
    std::cin >> n;
    
    Long lastPow = 0;
    std::set<Long> selected;
    for (Long pow = 1; selected.size() < n && pow <= MAX; pow *= 2) {
        selected.insert(pow);
        lastPow = pow;
    }
    for (Long i = MAX; selected.size() < n; --i) {
        if (selected.count(i) == 0) {
            selected.insert(i);
        }
    }

    std::cout << *selected.begin();
    for (auto it = std::next(selected.begin()); it != selected.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";
    std::cout.flush();
    
    for (int i = 0; i < n; ++i) {
        Long val;
        std::cin >> val;
        selected.insert(val);
    }

    Long sum = std::accumulate(selected.begin(), selected.end(), 0LL);
    Long goal = sum / 2;
    std::set<Long> answer;
    while (goal >= lastPow*2) {
        goal -= *std::prev(selected.end());
        answer.insert(*std::prev(selected.end()));
        selected.erase(std::prev(selected.end()));
    }

    for (Long pow = 1; goal > 0; pow *= 2) {
        if (goal & pow) {
            goal -= pow;
            answer.insert(pow);
        }
    }

    std::cout << *answer.begin();
    for (auto it = std::next(answer.begin()); it != answer.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";
    std::cout.flush();
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        solve();
    }

    return 0;
}