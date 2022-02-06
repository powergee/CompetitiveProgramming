#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

int query(int a, int b, int c) {
    printf("? %d %d %d\n", a, b, c);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

std::pair<int, int> filter(int a, int b, int c, int d) {
    std::pair<int, int> complements[4] {
        { query(b, c, d), a },
        { query(a, c, d), b },
        { query(a, b, d), c },
        { query(a, b, c), d }
    };
    std::sort(complements, complements+4);
    return { complements[0].second, complements[1].second };
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        std::queue<int> cands;
        for (int i = 1; i <= n; ++i) {
            cands.push(i);
        }

        while (cands.size() > 3) {
            int args[4];
            for (int i = 0; i < 4; ++i) {
                args[i] = cands.front();
                cands.pop();
            }
            auto [a, b] = filter(args[0], args[1], args[2], args[3]);
            cands.push(a);
            cands.push(b);
        }

        if (cands.size() == 3) {
            int args[4];
            for (int i = 0; i < 3; ++i) {
                args[i] = cands.front();
                cands.pop();
            }
            for (int i = 1; i <= n; ++i) {
                if (std::find(args, args+3, i) == args+3) {
                    args[3] = i;
                    break;
                }
            }
            auto [a, b] = filter(args[0], args[1], args[2], args[3]);
            cands.push(a);
            cands.push(b);
        }

        int a = cands.front();
        cands.pop();
        int b = cands.front();
        cands.pop();
        printf("! %d %d\n", a, b);
        fflush(stdout);
    }

    return 0;
}