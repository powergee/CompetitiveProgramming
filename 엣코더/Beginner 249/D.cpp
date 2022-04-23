#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAX 200000

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n);
    std::vector<std::set<int>> count(MAX+1);
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        arr[i] = v;
        count[v].insert(i);
    }

    Long answer = 0;
    for (Long v1 = 1; v1 <= MAX; ++v1) {
        for (Long v2 = 1; v2*v1 <= MAX; ++v2) {
            answer += Long(count[v1].size()) * Long(count[v2].size()) * Long(count[v1*v2].size());
        }
    }
    printf("%lld", answer);

    return 0;
}