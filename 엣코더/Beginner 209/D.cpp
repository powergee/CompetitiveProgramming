#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> graph[100001];
bool visited[100001];
bool color[100001];

void setColorFrom(int start, bool colorToSet) {
    color[start] = colorToSet;
    visited[start] = true;

    for (int next : graph[start]) {
        if (!visited[next]) {
            setColorFrom(next, !colorToSet);
        }
    }
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    setColorFrom(1, false);

    while (q--) {
        int c, d;
        scanf("%d %d", &c, &d);
        if (color[c] == color[d]) {
            printf("Town\n");
        } else {
            printf("Road\n");
        }
    }

    return 0;
}