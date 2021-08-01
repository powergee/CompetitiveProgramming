#include <iostream>
#include <algorithm>

int counter = 0;
int killers[200001];

void addEdge(int u, int v) {
    int min = std::min(u, v);
    killers[min]++;
    if (killers[min] == 1) {
        ++counter;
    }
}

void removeEdge(int u, int v) {
    int min = std::min(u, v);
    killers[min]--;
    if (killers[min] == 0) {
        --counter;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int com, u, v;
        scanf("%d", &com);

        switch (com)
        {
        case 1:
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            break;
        
        case 2:
            scanf("%d %d", &u, &v);
            removeEdge(u, v);
            break;

        case 3:
            printf("%d\n", n-counter);
            break;
        }
    }

    return 0;
}