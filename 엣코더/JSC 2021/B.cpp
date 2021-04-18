#include <iostream>
#include <set>

int main() {
    int n, m;
    std::set<int> a, b, c;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        a.insert(val);
        c.insert(val);
    }

    for (int i = 0; i < m; ++i) {
        int val;
        scanf("%d", &val);
        b.insert(val);
        c.insert(val);
    }

    std::set<int> answer;
    for (int v : c) {
        int exist = 0;
        if (a.find(v) != a.end()) {
            ++exist;
        }

        if (b.find(v) != b.end()) {
            ++exist;
        }

        if (exist == 1) {
            answer.insert(v);
        }
    }

    for (int i : answer) {
        std::cout << i << " ";
    }

    return 0;
}