#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    Long n, k;
    scanf("%lld %lld", &n, &k);

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }

    std::vector<bool> visited(n, false);
    std::vector<int> cycle;
    std::function<void(int)> findCycle = [&](int start) {
        if (visited[start]) {
            cycle.push_back(start);
            int curr = (start+arr[start]) % n;
            while (curr != start) {
                cycle.push_back(curr);
                curr = (curr+arr[curr]) % n;
            }
            return;
        }
        visited[start] = true;
        findCycle((start+arr[start]) % n);
    };
    findCycle(0);
    
    std::vector<int> entry;
    int curr = 0;
    while (curr != cycle.front()) {
        entry.push_back(curr);
        curr = (curr+arr[curr]) % n;
    }

    Long answer = 0;
    for (int i = 0; i < std::min(k, (Long)entry.size()); ++i) {
        answer += arr[entry[i]];
    }
    
    if (entry.size() < k) {
        if (k <= entry.size()+cycle.size()) {
            for (int i = 0; i < Long(k)-Long(entry.size()); ++i) {
                answer += arr[cycle[i]];
            }
        } else {
            Long subSum = 0;
            for (int i = 0; i < cycle.size(); ++i) {
                subSum += arr[cycle[i]];
            }
            answer += subSum * ((k-entry.size()) / cycle.size());
            for (int i = 0; i < ((k-entry.size()) % cycle.size()); ++i) {
                answer += arr[cycle[i]];
            }
        }
    }

    printf("%lld", answer);

    return 0;
}