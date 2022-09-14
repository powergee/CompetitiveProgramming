#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

typedef long long Long;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<Long>> intervals(m+1);
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        intervals[a].push_back(b);
    }

    std::vector<Long> left(m+1), right(m+1);
    
    for (int i = 0; i <= 2*m; ++i) {
        
    }

    return 0;
}