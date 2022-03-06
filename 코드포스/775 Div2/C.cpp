#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<Long>> table(n, std::vector<Long>(m));
    std::vector<std::vector<Long>> xOfColor(100001), yOfColor(100001);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%lld", &table[i][j]);
            xOfColor[table[i][j]].push_back(i);
            yOfColor[table[i][j]].push_back(j);
        }
    }

    Long answer = 0;
    for (auto& pos : xOfColor) {
        std::sort(pos.begin(), pos.end());
        Long sum = 0;
        for (int i = int(pos.size())-1; i >= 0; --i) {
            answer += sum - pos[i] * (Long(pos.size())-1-i);
            sum += pos[i];
        }
    }
    for (auto& pos : yOfColor) {
        std::sort(pos.begin(), pos.end());
        Long sum = 0;
        for (int i = int(pos.size())-1; i >= 0; --i) {
            answer += sum - pos[i] * (Long(pos.size())-1-i);
            sum += pos[i];
        }
    }

    printf("%lld", answer);

    return 0;
}