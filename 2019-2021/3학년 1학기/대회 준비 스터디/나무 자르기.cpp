#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n;
    long long answer = 0;
    std::vector<int> growth;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int init;
        scanf("%d", &init);
        answer += init;
    }

    for (int i = 0; i < n; ++i) {
        int g;
        scanf("%d", &g);
        growth.push_back(g);
    }

    std::sort(growth.begin(), growth.end());
    for (long long i = 0; i < n; ++i) {
        answer += i * growth[i];
    }

    printf("%lld", answer);

    return 0;
}