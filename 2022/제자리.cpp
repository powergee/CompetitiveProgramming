#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    int lookingFor = 1;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        if (lookingFor == v) {
            ++lookingFor;
        }
    }
    std::cout << n - (lookingFor-1);

    return 0;
}