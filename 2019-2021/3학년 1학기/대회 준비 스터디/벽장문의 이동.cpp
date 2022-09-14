#include <iostream>
#include <algorithm>

using State = std::pair<int, int>;

int queries[20];
int n, o1, o2, q;

int getMinCost(State s, int qIdx) {
    int qPos = queries[qIdx];

    if (q <= qIdx) {
        return 0;
    } else if (qPos == s.first || qPos == s.second) {
        return getMinCost(s, qIdx+1);
    } else if (qPos < s.first) {
        return s.first - qPos + getMinCost(State(qPos, s.second), qIdx+1);
    } else if (s.second < qPos) {
        return qPos - s.second + getMinCost(State(s.first, qPos), qIdx+1);
    } else {
        int r1 = qPos - s.first + getMinCost(State(qPos, s.second), qIdx+1);
        int r2 = s.second - qPos + getMinCost(State(s.first, qPos), qIdx+1);
        return std::min(r1, r2);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d %d", &o1, &o2);
    if (o2 < o1) {
        std::swap(o1, o2);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        scanf("%d", queries+i);
    }

    printf("%d", getMinCost(State(o1, o2), 0));

    return 0;
}