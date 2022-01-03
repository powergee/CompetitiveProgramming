#include <iostream>
#include <vector>
#include <set>

int query(int i) {
    printf("? %d\n", i);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> parent(n+1, -1);

        for (int i = 1; i <= n; ++i) {
            if (parent[i] != -1) {
                continue;
            }
            std::vector<int> appeared;
            std::set<int> appearedSet;
            bool loopDetected = false;
            
            while (!loopDetected) {
                int res = query(i);
                if (appearedSet.find(res) == appearedSet.end()) {
                    appearedSet.insert(res);
                    appeared.push_back(res);
                } else {
                    for (int i = 0; i < appeared.size(); ++i) {
                        parent[appeared[i]] = appeared[(i+1)%int(appeared.size())];
                    }
                    loopDetected = true;
                }
            }
        }

        printf("!");
        for (int i = 1; i <= n; ++i) {
            printf(" %d", parent[i]);
        }
        printf("\n");
        fflush(stdout);
    }

    return 0;
}