#include <iostream>
#include <queue>

int main() {
    int k, n;
    scanf("%d", &k);
    n = (1<<k)-1;

    int hist[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", hist+i);
    }

    std::queue<std::pair<int, int>> q;
    std::queue<int> answer;
    q.emplace(0, n-1);

    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        int m = (now.first + now.second) / 2;
        int root = hist[m];
        answer.push(root);

        if (now.first <= m-1) {
            q.emplace(now.first, m-1);
        }

        if (m+1 <= now.second) {
            q.emplace(m+1, now.second);
        }
    }

    int seg = 1;
    while (!answer.empty()) {
        for (int i = 0; i < seg; ++i) {
            printf("%d ", answer.front());
            answer.pop();
        }
        seg <<= 1;
        printf("\n");
    }

    return 0;
}