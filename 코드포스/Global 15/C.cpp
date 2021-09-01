#include <iostream>
#include <vector>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<std::pair<int, int>> edges;
        std::set<int> remain;
        for (int i = 1; i <= 2*n; ++i) {
            remain.insert(i);
        }

        for (int i = 0; i < k; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            if (u > v) {
                std::swap(u, v);
            }
            edges.emplace_back(u, v);
            remain.erase(remain.find(u));
            remain.erase(remain.find(v));
        }

        int answer = (int)remain.size()/2*((int)remain.size()/2-1) / 2;
        int paired[2*n+1] = {0,};
        std::vector<int> remVec(remain.begin(), remain.end());

        for (int i = 0; i < (int)remVec.size()/2; ++i) {
            paired[remVec[i]] = remVec[i+remVec.size()/2];
            paired[remVec[i+remVec.size()/2]] = remVec[i];
        }

        for (auto p : edges) {
            int add = 0;
            for (int i = 1; i <= 2*n; ++i) {
                if (paired[i] != 0) {
                    if (p.first < i && i < p.second) {
                        if (!(p.first < paired[i] && paired[i] < p.second)) {
                            ++add;
                        }
                    } else {
                        if (p.first < paired[i] && paired[i] < p.second) {
                            ++add;
                        }
                    }
                }
            }
            answer += add/2;
            paired[p.first] = p.second;
            paired[p.second] = p.first;
        }

        printf("%d\n", answer);
    }

    return 0;
}