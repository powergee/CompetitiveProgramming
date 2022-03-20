#include <iostream>
#include <set>

int main() {
    int n;
    scanf("%d", &n);

    std::set<int> nums;
    for (int i = 1; i <= 2*n+1; ++i) {
        nums.insert(i);
    }

    while (true) {
        printf("%d\n", *nums.begin());
        fflush(stdout);
        nums.erase(nums.begin());

        int val;
        scanf("%d", &val);
        if (val == 0) {
            break;
        } else {
            nums.erase(val);
        }
    }

    return 0;
}