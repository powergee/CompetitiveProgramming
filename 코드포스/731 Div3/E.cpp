#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

struct AirCon {
    Long pos, temp;

    AirCon(Long p, Long t) {
        pos = p;
        temp = t;
    }

    Long getTemp(Long p) const {
        if (p <= pos) {
            return -p + pos + temp;
        } else {
            return p - pos + temp;
        }
    }

    bool contains(const AirCon& other) const {
        Long p = other.pos;
        return this->getTemp(p) <= other.getTemp(p);
    }

    bool operator<(const AirCon& other) const {
        return pos < other.pos;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<AirCon> aircons(k, AirCon(0LL, 0LL));
        for (int i = 0; i < k; ++i) {
            scanf("%lld", &aircons[i].pos);
        }
        for (int i = 0; i < k; ++i) {
            scanf("%lld", &aircons[i].temp);
        }

        std::sort(aircons.begin(), aircons.end());

        std::vector<AirCon> airStack;
        for (int i = 0; i < k; ++i) {
            while (!airStack.empty() && aircons[i].contains(airStack.back())) {
                airStack.pop_back();
            }
            if (airStack.empty() || !airStack.back().contains(aircons[i])) {
                airStack.push_back(aircons[i]);
            }
        }

        std::vector<AirCon>::iterator it = airStack.begin();
        for (int i = 1; i <= n; ++i) {
            while (it+1 != airStack.end() && (it+1)->getTemp(i) <= it->getTemp(i)) {
                ++it;
            }
            printf("%lld ", it->getTemp(i));
        }
        printf("\n");
    }

    return 0;
}