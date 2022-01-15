#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
    int u, v, w = -1;

    int getOpposite(int s) {
        return u == s ? v : u;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> degree(n+1, 0);
        std::vector<Edge> edges(n-1);
        std::vector<std::vector<Edge*>> graph(n+1);
        for (int i = 0; i < n-1; ++i) {
            scanf("%d %d", &edges[i].u, &edges[i].v);
            degree[edges[i].u]++;
            degree[edges[i].v]++;
            graph[edges[i].u].push_back(&edges[i]);
            graph[edges[i].v].push_back(&edges[i]);
        }

        if (*std::max_element(degree.begin(), degree.end()) > 2) {
            printf("-1\n");
        } else {
            std::function<void(Edge*, int)> assignWeights;
            assignWeights = [&](Edge* e, int currWeight) -> void {
                e->w = currWeight;
                for (int next : std::vector<int> { e->u, e->v }) {
                    for (Edge* nextEdge : graph[next]) {
                        if (nextEdge->w == -1) {
                            int nextWeight = (currWeight == 3 ? 2 : 3);
                            assignWeights(nextEdge, nextWeight);
                        }
                    }
                }
            };

            assignWeights(&edges[0], 2);
            for (Edge& e : edges) {
                printf("%d ", e.w);
            }
            printf("\n");
        }
    }
    
    return 0;
}