#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

std::vector<int> in[1001], out[1001];
int prevVisited[1001];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int count;
        scanf("%d", &count);
        std::vector<int> singers(count);

        for (int j = 0; j < count; ++j) {
            scanf("%d", &singers[j]);
        }
        for (int j = 0; j < count-1; ++j) {
            int s1 = singers[j];
            int s2 = singers[j+1];
            out[s1].push_back(s2);
            in[s2].push_back(s1);
        }
    }

    int visited = 0;
    std::vector<int> answer;
    std::queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (in[v].empty()) {
            q.push(v);
            visited++;
        }
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        answer.push_back(curr);
        
        for (int next : out[curr]) {
            prevVisited[next]++;
            if (prevVisited[next] == in[next].size()) {
                q.push(next);
                visited++;
            }
        }
    }

    if (visited == n) {
        for (int v : answer) {
            printf("%d\n", v);
        }
    } else {
        printf("0");
    }

    return 0;
}