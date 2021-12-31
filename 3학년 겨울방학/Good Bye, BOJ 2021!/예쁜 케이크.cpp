#include <iostream>
#include <set>

typedef long long Long;

bool isPossible(Long n) {
    const static std::set<Long> TARGET { 0LL, 2LL, 5LL, 8LL };
    return TARGET.find(n%9) != TARGET.end();
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);
        if (isPossible(n)) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }

    return 0;
}