#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int u, v, d;

    int getOpposite(int p) {
        return p == u ? v : u;
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<Edge> edges(n-1);
    std::vector<std::vector<Edge*>> tree(n+1);
    std::vector<int> skill(k), answer(n+1, 0);

    for (int i = 0; i < n-1; ++i) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        edges[i] = {u, v, d};
        tree[u].push_back(&edges[i]);
        tree[v].push_back(&edges[i]);
    }

    for (int i = 0; i < k; ++i) {
        scanf("%d", &skill[i]);
    }
    std::sort(skill.begin(), skill.end());

    std::vector<bool> visited(n+1, false);
    std::function<void(int, int, int)> DFS = [&](int start, int idxStart, int idxEnd) -> void {
        visited[start] = true;
        answer[start] = idxEnd-idxStart+1;

        std::vector<Edge*> downhills;
        for (Edge* hill : tree[start]) {
            if (visited[hill->u] ^ visited[hill->v]) {
                downhills.push_back(hill);
            }
        }

        if (!downhills.empty()) {
            std::sort(downhills.begin(), downhills.end(), [](Edge* e1, Edge* e2) -> bool {
                return e1->d < e2->d;
            });

            for (int i = 0; i+1 < downhills.size() && idxStart <= idxEnd; ++i) {
                int bound = (downhills[i]->d + downhills[i+1]->d) / 2;
                auto found = std::upper_bound(skill.begin()+idxStart, skill.begin()+idxEnd+1, bound);
                int currEnd = found-skill.begin()-1;
                if (idxStart <= currEnd) {
                    DFS(downhills[i]->getOpposite(start), idxStart, currEnd);
                    idxStart = currEnd+1;
                }
            }

            if (idxStart <= idxEnd) {
                DFS(downhills.back()->getOpposite(start), idxStart, idxEnd);
            }
        }
    };
    DFS(1, 0, k-1);

    for (int i = 1; i <= n; ++i) {
        printf("%d", answer[i]);
        if (i != n) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}