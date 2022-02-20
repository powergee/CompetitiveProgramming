#include <iostream>
#include <stack>

int main() {
    int n;
    scanf("%d", &n);

    std::stack<std::pair<int, int>> cylinder;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);

        if (cylinder.empty() || cylinder.top().first != a) {
            cylinder.emplace(a, 1);
        } else if (cylinder.top().first == a) {
            if (cylinder.top().second == a-1) {
                while (!cylinder.empty() && cylinder.top().first == a) {
                    cylinder.pop();
                }
            } else {
                cylinder.emplace(a, cylinder.top().second+1);
            }
        }
        
        printf("%d\n", (int)cylinder.size());
    }

    return 0;
}