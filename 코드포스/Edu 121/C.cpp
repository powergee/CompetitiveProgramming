#include <iostream>
#include <vector>

typedef long long Long;

struct Spell {
    Long start, end;

    Long getMana() {
        Long n = end-start+1;
        return n*(n+1)/2;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Long> time(n), health(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &time[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &health[i]);
        }

        std::vector<Spell> spells;
        for (int i = 0; i < n; ++i) {
            Spell current = { time[i]-health[i]+1, time[i] };

            while (!spells.empty() && current.start <= spells.back().start) {
                spells.pop_back();
            }

            if (spells.empty() || spells.back().end < current.start) {
                spells.push_back(current);
            } else {
                spells.back().end = current.end;
            }
        }

        Long sum = 0;
        for (auto s : spells) {
            sum += s.getMana();
        }
        printf("%lld\n", sum);
    }

    return 0;
}