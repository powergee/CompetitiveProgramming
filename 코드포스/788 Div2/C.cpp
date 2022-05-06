#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

typedef long long Long;

Long getModOfPow(Long a, Long b, Long c) {
    if (b == 0LL) {
        return 1LL % c;
    } else if (b == 1LL) {
        return a % c;
    } else if (b % 2LL == 0LL) {
        Long sub = getModOfPow(a, b/2LL, c);
        return (sub*sub) % c;
    } else {
        return (getModOfPow(a, b-1, c) * (a%c)) % c;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> a(n), b(n), c(n);
        std::vector<std::vector<int>> indexBucket(n+1);
        std::vector<std::set<int>> graph(n+1); 
        std::vector<bool> confirmed(n, false);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            indexBucket[a[i]].push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
            indexBucket[b[i]].push_back(i);
        }
        for (int i = 1; i < n+1; ++i) {
            graph[indexBucket[i][0]].insert(indexBucket[i][1]);
            graph[indexBucket[i][1]].insert(indexBucket[i][0]);
        }

        std::function<void(int, int)> setValue = [&](int start, int value) {
            if (c[start]) { return; }
            c[start] = value;
            int other = (a[start] == value ? b[start] : a[start]);
            
            int next = (start == indexBucket[value][0] ? indexBucket[value][1] : indexBucket[value][0]);
            setValue(next, (value == a[next] ? b[next] : a[next]));

            next = (start == indexBucket[other][0] ? indexBucket[other][1] : indexBucket[other][0]);
            setValue(next, other);
        };

        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (val != 0) {
                setValue(i, val);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                c[i] = a[i];
            }
        }

        std::vector<bool> visited(n, false);
        std::function<void(int)> DFS = [&](int start) {
            visited[start] = true;
            for (int next : graph[start]) {
                if (!visited[next]) {
                    DFS(next);
                }
            }
        };
        int compCount = 0;
        for (int i = 0; i < n; ++i) {
            if (c[i] == 0 && !visited[i]) {
                DFS(i);
                compCount++;
            }
        }

        printf("%lld\n", getModOfPow(2, compCount, 1000000007LL));
    }

    return 0;
}