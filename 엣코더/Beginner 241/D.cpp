#include <iostream>
#include <set>

typedef long long Long;

int main() {
    int q;
    scanf("%d", &q);

    std::multiset<Long, std::less<Long>> asc;
    std::multiset<Long, std::greater<Long>> dec;
    for (int i = 0; i < q; ++i) {
        int op;
        scanf("%d", &op);

        switch (op)
        {
            case 1: {
                Long x;
                scanf("%lld", &x);
                asc.insert(x);
                dec.insert(x);
                break;
            }

            case 2: {
                Long x, k;
                scanf("%lld %lld", &x, &k);
                auto it = asc.upper_bound(x);
                bool valid = true;
                for (int j = 0; j < k; ++j) {
                    if (it == asc.begin()) {
                        valid = false;
                        break;
                    } else {
                        it = std::prev(it);
                    }
                }
                if (valid) {
                    printf("%lld\n", *it);
                } else {
                    printf("-1\n");
                }
                break;
            }

            case 3: {
                Long x, k;
                scanf("%lld %lld", &x, &k);
                auto it = dec.upper_bound(x);
                bool valid = true;
                for (int j = 0; j < k; ++j) {
                    if (it == dec.begin()) {
                        valid = false;
                        break;
                    } else {
                        it = std::prev(it);
                    }
                }
                if (valid) {
                    printf("%lld\n", *it);
                } else {
                    printf("-1\n");
                }
                break;
            }
        }
    }

    return 0;
}