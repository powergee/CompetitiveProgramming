#include <iostream>
#include <vector>

bool isSorted(std::vector<int>& vec) {
    for (int i = 0; i+1 < vec.size(); ++i) {
        if (vec[i] > vec[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> even, odd;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            (val % 2 == 0 ? even : odd).push_back(val);
        }

        if (isSorted(even) && isSorted(odd)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}