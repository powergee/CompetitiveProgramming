#include <iostream>
#include <queue>
#include <functional>

int main() {
    int n;
    scanf("%d", &n);

    std::priority_queue<int, std::vector<int>, std::less<int>> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;

    int val;
    scanf("%d", &val);
    left.push(val);
    printf("%d\n", val);

    for (int i = 2; i <= n; ++i) {
        scanf("%d", &val);
        if (val <= left.top()) {
            left.push(val);
            while ((i % 2 == 0 && left.size() > right.size()) || 
                   (i % 2 != 0 && left.size() > right.size()+1)) {
                right.push(left.top());
                left.pop();
            }
        } else {
            right.push(val);
            while (left.size() < right.size()) {
                left.push(right.top());
                right.pop();
            }
        }
        printf("%d\n", left.top());
    }

    return 0;
}