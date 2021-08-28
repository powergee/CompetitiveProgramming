#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Count {
    int a, b, c;

    Count(int pa, int pb, int pc) {
        a = pa;
        b = pb;
        c = pc;
    }

    Count() : Count(0, 0, 0) {}

    Count operator+(const Count& other) const {
        Count result = {
            a + other.a,
            b + other.b,
            c + other.c
        };
        return result;
    }

    Count operator-(const Count& other) const {
        Count result = {
            a - other.a,
            b - other.b,
            c - other.c
        };
        return result;
    }

    int operator[](char ch) const {
        if (ch == 'a') {
            return a;
        } else if (ch == 'b') {
            return b;
        } else {
            return c;
        }
    }

    int getSum() const {
        return a+b+c;
    }
} count[3][200000];

Count getCountInRange(int left, int right, int m) {
    if (left == 0) {
        return count[m][right];
    }
    return count[m][right] - count[m][left-1];
}

char str[200001];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", str);

    count[0][0] = {
        (str[0] == 'a' ? 1 : 0),
        (str[0] == 'b' ? 1 : 0),
        (str[0] == 'c' ? 1 : 0)
    };
    for (int i = 1; i < n; ++i) {
        for (int m = 0; m < 3; ++m) {
            if (m == (i%3)) {
                count[m][i] = count[m][i-1] + Count(
                    (str[i] == 'a' ? 1 : 0),
                    (str[i] == 'b' ? 1 : 0),
                    (str[i] == 'c' ? 1 : 0)
                );
            } else {
                count[m][i] = count[m][i-1];
            }
        }
    }

    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        --l; --r;

        int minDiff = __INT32_MAX__;
        std::string seg = "abc";
        do {
            int diff = 0;
            for (int m = 0; m < 3; ++m) {
                Count total = getCountInRange(l, r, m);
                diff += total.getSum() - total[seg[m]];
            }
            minDiff = std::min(minDiff, diff);
        } while (std::next_permutation(seg.begin(), seg.end()));

        printf("%d\n", minDiff);
    }

    return 0;
}