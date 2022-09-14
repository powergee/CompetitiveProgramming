#include <iostream>
#include <set>
#include <vector>

typedef long long Long;

class Festival {
private:
    int k;
    Long sum = 0;
    std::multiset<int> bestOnes, spares;

    void fixBalance() {
        while (k < bestOnes.size()) {
            spares.insert(*bestOnes.begin());
            sum -= *bestOnes.begin();
            bestOnes.erase(bestOnes.begin());
        }
        while (!spares.empty() && bestOnes.size() < k) {
            auto iter = std::prev(spares.end());
            bestOnes.insert(*iter);
            sum += *iter;
            spares.erase(iter);
        }
    }

public:
    Festival(int k) {
        this->k = k;
    }

    void push(int val) {
        bestOnes.insert(val);
        sum += val;
        fixBalance();
    }

    void pop(int val) {
        auto found = bestOnes.find(val);
        if (found != bestOnes.end()) {
            sum -= *found;
            bestOnes.erase(found);
        } else {
            spares.erase(spares.find(val));
        }
        fixBalance();
    }

    Long sumTops() {
        return sum;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);;

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        int d, n, k;
        std::cin >> d >> n >> k;
        std::vector<std::vector<int>> start(d+1), end(d+1);

        for (int i = 0; i < n; ++i) {
            int h, s, e;
            std::cin >> h >> s >> e;
            start[s].push_back(h);
            end[e].push_back(h);
        }

        Long answer = 0;
        Festival fesSet(k);
        for (int i = 1; i <= d; ++i) {
            for (int h : start[i]) {
                fesSet.push(h);
            }
            answer = std::max(answer, fesSet.sumTops());
            for (int h : end[i]) {
                fesSet.pop(h);
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}