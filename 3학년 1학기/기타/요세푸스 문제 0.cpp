#include <iostream>
#include <queue>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i);
    }

    int index = 1;
    printf("<");
    while (!q.empty()) {
        if (index == k) {
            int terminated = q.front();
            q.pop();
            printf("%d", terminated);
            if (!q.empty()) {
                printf(", ");
            }
            index = 1;
        } else {
            ++index;
            int moved = q.front();
            q.pop();
            q.push(moved);
        }
    }
    printf(">");

    return 0;
}