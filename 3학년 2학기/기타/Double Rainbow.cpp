#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <map>

class CountSet {
private:
    int size = 0;
    std::map<int, int> count;

public:
    void add(int val) {
        count[val]++;
        if (count[val] == 1) {
            size++;
        }
    }

    void remove(int val) {
        count[val]--;
        if (count[val] == 0) {
            size--;
        }
    }
    
    int getSize() {
        return size;
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    CountSet inner, outer;
    int arr[10000];
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        outer.add(arr[i]);
    }

    int answer = INT32_MAX;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && inner.getSize() < k) {
            inner.add(arr[j]);
            outer.remove(arr[j]);
            ++j;
        }
        if (inner.getSize() == k && outer.getSize() == k) {
            answer = std::min(answer, j-i);
        }
        inner.remove(arr[i]);
        outer.add(arr[i]);
    }

    printf("%d", (answer == INT32_MAX ? 0 : answer));

    return 0;
}
