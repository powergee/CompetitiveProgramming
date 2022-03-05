#include <iostream>
#include <string>
#include <vector>

typedef long long Long;

char stepLeftMost(char curr, Long count) {
    return "ABC"[(count + (curr - 'A')) % 3];
}

char stepRightMost(char curr, Long count) {
    return "CBA"[(count + (2 - (curr - 'A'))) % 3];
}

char findChar(char root, Long height, Long pos) {
    if (height == 0) {
        return root;
    }
    if (height > 62) {
        return findChar(stepLeftMost(root, height-62), 62, pos);
    }

    if (pos <= (1LL<<(height-1))-1) {
        return findChar(stepLeftMost(root, 1), height-1, pos);
    } else {
        return findChar(stepRightMost(root, 1), height-1, pos-(1LL<<(height-1)));
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string line;
    std::cin >> line;
    int n = line.size();

    int q;
    std::cin >> q;

    std::vector<std::pair<Long, Long>> queries(q);
    for (int i = 0; i < q; ++i) {
        Long t, k;
        std::cin >> t >> k;
        queries[i] = { t, k };
    }

    for (auto [t, k] : queries) {
        char root;
        Long pos;
        if (t <= 62) {
            Long rootLength = (1LL << t);
            root = line[(k-1) / rootLength];
            pos = (k-1) - ((k-1) / rootLength * rootLength);
        } else {
            root = line[0];
            pos = k-1;
        }

        // printf("%c %lld %lld\n", root, t, pos);
        printf("%c\n", findChar(root, t, pos));
    }

    return 0;
}