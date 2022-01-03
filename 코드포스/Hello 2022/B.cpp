#include <iostream>
#include <vector>
#include <set>

struct Segment {
    int l, r, c;

    bool operator<(const Segment& s) const {
        if (c != s.c) {
            return c < s.c;
        }
        if (l != s.l) {
            return l < s.l;
        }
        return r < s.r;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Segment> segs(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d", &segs[i].l, &segs[i].r, &segs[i].c);
        }
        
        std::set<Segment> left, right, whole;
        left.insert(segs[0]);
        right.insert(segs[0]);
        whole.insert(segs[0]);

        printf("%d\n", segs[0].c);
        for (int i = 1; i < n; ++i) {
            if (segs[i].l < left.begin()->l) {
                left = { segs[i] };
            } else if (segs[i].l == left.begin()->l) {
                left.insert(segs[i]);
            }

            if (right.begin()->r < segs[i].r) {
                right = { segs[i] };
            } else if (right.begin()->r == segs[i].r) {
                right.insert(segs[i]);
            }

            Segment wholeRange = { left.begin()->l, right.begin()->r, -1 };
            if (whole.begin()->l != wholeRange.l || whole.begin()->r != wholeRange.r) {
                whole.clear();
            }
            if (wholeRange.l == segs[i].l && wholeRange.r == segs[i].r) {
                whole.insert(segs[i]);
            }

            int cost = left.begin()->c + right.begin()->c;
            if (!whole.empty()) {
                cost = std::min(cost, whole.begin()->c);
            }
            printf("%d\n", cost);
        }
    }

    return 0;
}