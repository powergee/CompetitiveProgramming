#include <iostream>
#include <queue>
#include <set>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    Long arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", arr+i);
    }

    int answerK = 0;
    Long answerDiff = INT64_MAX;
    for (int k = 1; k <= n/2; ++k) {
        Long curr = 0;
        for (int i = 0; i < k; ++i) {
            curr += arr[i];
        }
        std::queue<Long> q;
        q.push(curr);
        std::set<Long> leftSet;
        
        Long minDiff = INT64_MAX;
        for (int i = 1; i+k-1 < n; ++i) {
            if (q.size() >= k) {
                leftSet.insert(q.front());
                q.pop();
            }
            curr -= arr[i-1];
            curr += arr[i+k-1];
            
            auto lower = leftSet.lower_bound(curr);
            if (lower != leftSet.end()) {
                minDiff = std::min(minDiff, *lower - curr);
            }
            if (lower != leftSet.begin()) {
                auto prevLower = std::prev(lower);
                minDiff = std::min(minDiff, curr - *prevLower);
            }
            q.push(curr);
        }

        if (minDiff <= answerDiff) {
            answerDiff = minDiff;
            answerK = k;
        }
    }

    printf("%d\n%lld", answerK, answerDiff);

    return 0;
}