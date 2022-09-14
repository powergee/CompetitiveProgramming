#include <iostream>
#include <algorithm>

void mergeSet(int a, int b);
int findRoot(int a);

int plan[200000];
int parent[200000];
int answer[200000];

void mergeSet(int a, int b) {
    int ar = findRoot(a);
    int br = findRoot(b);

    if (ar != br) {
        parent[ar] = br;
    }
}

int findRoot(int a) {
    if (parent[a] == -1) {
        return a;
    }

    return parent[a] = findRoot(parent[a]);
}

int main() {
    int n;
    scanf("%d", &n);
    std::fill(parent, parent+n, -1);

    for (int i = 0; i < n; ++i) {
        scanf("%d", plan+i);
    }

    int k = *std::max_element(plan, plan+n)+1;
    std::fill(answer, answer+k, -1);

    for (int i = 0; i < n-1; ++i) {
        if (findRoot(plan[i]) != findRoot(plan[i+1])) {
            answer[plan[i+1]] = plan[i];
            mergeSet(plan[i], plan[i+1]);
        }
    }

    printf("%d\n", k);
    for (int i = 0; i < k; ++i) {
        printf("%d ", answer[i]);
    }

    return 0;
}