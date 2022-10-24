#include <iostream>
#include <cassert>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::set<int> q;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        if (q.count(-v)) {
            q.erase(-v);
        } else {
            q.insert(v);
        }
    }

    assert(q.size() == 2);
    int a = *q.begin();
    q.erase(q.begin());
    int b = *q.begin();
    std::cout << a+b;

    return 0;
}