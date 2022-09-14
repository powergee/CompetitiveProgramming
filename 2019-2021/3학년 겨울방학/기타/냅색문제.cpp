#include <iostream>
#include <map>
#include <vector>

typedef long long Long;

std::map<Long, Long> countCases(std::vector<Long> items) {
    std::map<Long, Long> count;
    for (int mask = 0; mask < (1 << items.size()); ++mask) {
        Long sum = 0;
        for (int i = 0; i < items.size(); ++i) {
            if (mask & (1<<i)) {
                sum += items[i];
            }
        }
        count[sum]++;
    }
    return count;
}

std::vector<std::pair<Long, Long>> getPrefixSum(std::map<Long, Long> count) {
    std::vector<std::pair<Long, Long>> sum(count.begin(), count.end());
    for (int i = 1; i < sum.size(); ++i) {
        sum[i].second += sum[i-1].second;
    }
    return sum;
}

int main() {
    Long n, c;
    scanf("%lld %lld", &n, &c);
    
    std::vector<Long> items(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &items[i]);
    }

    if (n == 1) {
        printf("%d", items[0] <= c ? 2 : 1);
        return 0;
    }

    auto c1 = countCases(std::vector<Long>(items.begin(), items.begin()+(n/2+1)));
    auto c2 = getPrefixSum(countCases(std::vector<Long>(items.begin()+(n/2+1), items.end())));

    Long answer = 0;
    for (auto p : c1) {
        auto found = std::lower_bound(c2.begin(), c2.end(), std::make_pair(c-p.first, 0LL));
        if (found == c2.end()) {
            answer += c2.back().second * p.second;
        } else if (found->first == c-p.first) {
            answer += found->second * p.second;
        } else if (found != c2.begin()) {
            answer += std::prev(found)->second * p.second;
        }
    }

    printf("%lld", answer);

    return 0;
}