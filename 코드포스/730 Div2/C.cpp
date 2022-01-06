#include <iostream>
#define PADDING 10000000

typedef long long Long;

struct State {
    Long c, m, p, v;

    int countNonZeros() {
        return (c > 0 ? 1 : 0) + (m > 0 ? 1 : 0) + (p > 0 ? 1 : 0);
    }

    State drawCash() {
        State result = *this;
        Long reduced;
        if (c <= v) {
            reduced = c;
        } else {
            reduced = v;
        }

        result.c -= reduced;
        int x = result.countNonZeros() - (result.c > 0 ? 1 : 0);
        if (result.m > 0) {
            result.m += reduced / x;
        }
        if (result.p > 0) {
            result.p += reduced / x;
        }
        return result;
    }

    State drawMarker() {
        State result = *this;
        Long reduced;
        if (m <= v) {
            reduced = m;
        } else {
            reduced = v;
        }

        result.m -= reduced;
        int x = result.countNonZeros() - (result.m > 0 ? 1 : 0);
        if (result.c > 0) {
            result.c += reduced / x;
        }
        if (result.p > 0) {
            result.p += reduced / x;
        }
        return result;
    }
};



Long calcExp(State current, int prevUsed) {
    Long result = current.p * (prevUsed+1);
    if (current.c > 0) {
        result += current.c * calcExp(current.drawCash(), prevUsed+1) / PADDING;
    }
    if (current.m > 0) {
        result += current.m * calcExp(current.drawMarker(), prevUsed+1) / PADDING;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        double c, m, p, v;
        scanf("%lf %lf %lf %lf", &c, &m, &p, &v);

        State init = {
            (Long)(c*PADDING),
            (Long)(m*PADDING),
            (Long)(p*PADDING),
            (Long)(v*PADDING),
        };
        printf("%.10lf\n", (double)calcExp(init, 0) / PADDING);
    }

    return 0;
}