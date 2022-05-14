#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<Long> arr(n);
    std::pair<Long, Long> globalUpdate = {-1, -1};
    std::vector<std::pair<Long, Long>> indivUpdate(n, {-1, -1});
    Long sum = 0;
    
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
        sum += arr[i];
    }

    auto getValue = [&](int index) {
        Long result = arr[index];
        auto update = std::max(globalUpdate, indivUpdate[index]);
        if (update.second != -1) {
            result = update.second;
        }
        return result;
    };

    int timeStamp = 0;
    while (q--) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            Long i, x;
            scanf("%lld %lld", &i, &x);
            --i;
            Long prevVal = getValue(i);
            indivUpdate[i] = { timeStamp++, x };
            Long currVal = getValue(i);
            sum += (currVal-prevVal);
        } else {
            Long x;
            scanf("%lld", &x);
            globalUpdate = { timeStamp++, x };
            sum = x*n;
        }
        
        printf("%lld\n", sum);
    }

    return 0;
}