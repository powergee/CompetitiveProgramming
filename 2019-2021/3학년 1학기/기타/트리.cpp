#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::vector<int> graph[50];
    int root, n;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int par;
        scanf("%d", &par);
        if (par == -1) {
            root = i;
        } else {
            graph[par].push_back(i);
        }
    }

    int remove, count = 0;
    scanf("%d", &remove);
    std::queue<int> q;
    q.push(root);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == remove) {
            continue;
        }
        if (graph[curr].empty() ||
            graph[curr].size() == 1 && graph[curr].front() == remove) {
            ++count;
        }

        for (int next : graph[curr]) {
            q.push(next);
        }
    }

    printf("%d", count);
    return 0;
}