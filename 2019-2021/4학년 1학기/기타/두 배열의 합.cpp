#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    int t;
    scanf("%d", &t);

    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int m;
    scanf("%d", &m);
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    std::map<int, int> aSubCount;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j < n; ++j) {
            sum += a[j];
            aSubCount[sum]++;
        }
    }

    long long answer = 0;
    for (int i = 0; i < m; ++i) {
        int sum = 0;
        for (int j = i; j < m; ++j) {
            sum += b[j];
            answer += aSubCount[t-sum];
        }
    }

    printf("%lld", answer);

    return 0;
}