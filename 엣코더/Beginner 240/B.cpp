#include <iostream>
#include <set>

int main() {
    int n;
    scanf("%d", &n);

    std::set<int> arr;
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        arr.insert(v);
    }

    printf("%d", int(arr.size()));
    return 0;
}