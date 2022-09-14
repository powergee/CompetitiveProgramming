#include <iostream>
#include <algorithm>
#include <set>

struct Gem {
    int weight;
    int value;

    bool operator<(const Gem& g) const {
        if (value != g.value) {
            return value > g.value;
        } else {
            return weight < g.weight;
        }
    }
};

Gem gems[300000];
std::multiset<int> caps;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        int m, v;
        scanf("%d %d", &m, &v);
        gems[i] = {m, v};
    }

    for (int i = 0; i < k; ++i) {
        int c;
        scanf("%d", &c);
        caps.insert(c);
    }

    std::sort(gems, gems + n);

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        auto& g = gems[i];
        auto found = caps.lower_bound(g.weight);
        if (found != caps.end()) {
            sum += g.value;
            caps.erase(found);
        }
    }

    printf("%lld", sum);

    return 0;
}