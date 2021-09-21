#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define BUCKET_SIZE 19999999

int a[4000], b[4000], c[4000], d[4000];

class HashCounter {
private:
    std::vector<int>* count;

public:
    HashCounter() {
        count = new std::vector<int>[BUCKET_SIZE];
    }

    void addValue(int val) {
        val += (1<<29);
        count[val % BUCKET_SIZE].push_back(val);
    }
    
    void sortBuckets() {
        for (int i = 0; i < BUCKET_SIZE; ++i) {
            std::sort(count[i].begin(), count[i].end());
        }
    }

    int countValue(int val) {
        val += (1<<29);
        int i = val % BUCKET_SIZE;
        return int(std::upper_bound(count[i].begin(), count[i].end(), val) - std::lower_bound(count[i].begin(), count[i].end(), val));
    }
};

int main() {
    HashCounter left;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", a+i, b+i, c+i, d+i);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            left.addValue(a[i]+b[j]);
        }
    }
    left.sortBuckets();

    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            answer += left.countValue(-c[i]-d[j]);
        }
    }

    printf("%lld", answer);
    
    return 0;
}