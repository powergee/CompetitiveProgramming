#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> rows[1000001];
int count[1000001];

int main() {
    int n, m, t, k;
    scanf("%d %d %d %d", &n, &m, &t, &k);

    for (int i = 0; i < t; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        rows[b].push_back(a);
    }

    int x, y;
    int answer = 0;
    for (int r = 0; r <= k; ++r) {
        for (int c : rows[r]) {
            for (int i = std::max(c-k, 0); i <= std::min(c, n-k); ++i) {
                count[i]++;
            }
        }
    }
    for (int c = 0; c <= n-k; ++c) {
        if (answer < count[c]) {
            answer = count[c];
            x = c;
            y = k;
        }
    }

    std::vector<int> changed;
    for (int r = k+1; r <= m; ++r) {
        for (int c : rows[r-k-1]) {
            for (int i = std::max(c-k, 0); i <= std::min(c, n-k); ++i) {
                count[i]--;
                changed.push_back(i);
            }
        }
        for (int c : rows[r]) {
            for (int i = std::max(c-k, 0); i <= std::min(c, n-k); ++i) {
                count[i]++;
                changed.push_back(i);
            }
        }
        for (int c : changed) {
            if (answer < count[c]) {
                answer = count[c];
                x = c;
                y = r;
            }
        }
        changed.resize(0);
    }

    printf("%d %d\n", x, y);
    printf("%d\n", answer);

    return 0;
}
