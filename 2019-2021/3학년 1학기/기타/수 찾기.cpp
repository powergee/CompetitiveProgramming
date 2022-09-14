#include <iostream>
#include <unordered_set>

int main() {
    int n, m;
    std::unordered_set<int> nums;
    scanf("%d", &n);

    while (n--) {
        int num;
        scanf("%d", &num);
        nums.insert(num);
    }

    scanf("%d", &m);

    while (m--) {
        int num;
        scanf("%d", &num);
        if (nums.find(num) == nums.end()) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    
    return 0;
}