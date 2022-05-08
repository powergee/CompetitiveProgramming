#include <iostream>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int arr[n];
        std::set<int> arrSet;
        int nonZero = 0;
        bool hasDup = false;
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            if (arr[i] != 0) { ++nonZero; }
            if (arrSet.count(arr[i])) {
                hasDup = true;
            }
            arrSet.insert(arr[i]);
        }

        int zero = n-nonZero;
        if (zero) {
            printf("%d\n", nonZero);
        } else if (hasDup) {
            printf("%d\n", nonZero);
        } else {
            printf("%d\n", nonZero+1);
        }
    }

    return 0;
}