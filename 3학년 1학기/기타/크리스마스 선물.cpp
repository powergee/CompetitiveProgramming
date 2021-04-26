#include <iostream>
#include <queue>

int main() {
    int n;
    scanf("%d", &n);
    std::priority_queue<int> presents;

    while (n--) {
        int a;
        scanf("%d", &a);

        if (a == 0) {
            if (presents.empty()) {
                printf("-1\n");
            } else {
                int p = presents.top();
                presents.pop();
                printf("%d\n", p);
            }
        } else {
            while (a--) {
                int p;
                scanf("%d", &p);
                presents.push(p);
            }
        }
    }

    return 0;
}