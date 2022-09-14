#include <iostream>
#include <vector>
#include <queue>
#include <set>

typedef long long Long;

Long factorial(int n) {
    static Long dp[21];

    if (dp[n] != 0) {
        return dp[n];
    }

    Long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return dp[n] = fact;
}

void findArray(int n, Long k, std::vector<int>& answer, std::set<int>& unused) {
    if (n == (int)answer.size()) {
        return;
    }

    auto it = unused.begin();
    for (int i = 0; i < (int)unused.size(); ++i, ++it) {
        Long left = i*factorial((int)unused.size()-1)+1;
        Long right = (i+1)*factorial((int)unused.size()-1);
        if (left <= k && k <= right) {
            answer.push_back(*it);
            unused.erase(it);
            findArray(n, k-left+1, answer, unused);
            return;
        }
    }
}

Long findNumber(int n, std::queue<int>& arr, std::set<int>& unused) {
    if ((int)unused.size() == 0) {
        return 1LL;
    }

    auto it = unused.begin();
    for (int i = 0; i < (int)unused.size(); ++i, ++it) {
        if (*it == arr.front()) {
            Long left = i*factorial((int)unused.size()-1);
            arr.pop();
            unused.erase(it);
            return left + findNumber(n, arr, unused);
        }
    }

    return -1;
}

int main() {
    int n, op;
    scanf("%d%d", &n, &op);

    if (op == 1) {
        Long k;
        scanf("%lld", &k);
        std::vector<int> answer;
        std::set<int> unused;
        for (int i = 1; i <= n; ++i) {
            unused.insert(i);
        }
        findArray(n, k, answer, unused);
        for (int v : answer) {
            printf("%d ", v);
        }
    } else {
        std::queue<int> arr;
        std::set<int> unused;
        for (int i = 1; i <= n; ++i) {
            unused.insert(i);
        }
        for (int i = 0; i < n; ++i) {
            int v;
            scanf("%d", &v);
            arr.push(v);
        }
        printf("%lld", findNumber(n, arr, unused));
    }

    return 0;
}