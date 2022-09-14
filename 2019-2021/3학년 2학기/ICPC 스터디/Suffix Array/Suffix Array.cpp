#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

class ManberMyers {
private:
    int n;
    std::string str;
    std::vector<int> sa;
    std::vector<int> group;
    std::vector<int> lcp;

    void initSuffixArray() {
        int n = str.size();
        std::iota(sa.begin(), sa.end(), 0);
        std::transform(sa.begin(), sa.end(), group.begin(), [&](int i) -> int {
            return (int)str[i];
        });

        for (int d = 1; ; d <<= 1) {
            auto compareSuffix = [&](int s1, int s2) -> bool {
                if (group[s1] != group[s2]) {
                    return group[s1] < group[s2];
                } else if (s1+d < n && s2+d < n) {
                    return group[s1+d] < group[s2+d];
                } else {
                    return s1 > s2;
                }
            };
            std::sort(sa.begin(), sa.end(), compareSuffix);

            std::vector<int> newGroup(n, 0);
            for (int i = 0; i < n-1; ++i) {
                newGroup[i+1] = newGroup[i] + (compareSuffix(sa[i], sa[i+1]) ? 1 : 0);
            }
            for (int i = 0; i < n; ++i) {
                group[sa[i]] = newGroup[i];
            }

            if (newGroup.back() == n-1) {
                break;
            }
        }
    }

    void initLCP() {
        for (int i = 0, k = 0; i < n; ++i, k = std::max(k-1, 0)) {
            if (group[i] != n-1) {
                for (int j = sa[group[i]+1]; str[i+k] == str[j+k]; ++k);
                lcp[group[i]] = k;
            }
        }
    }

public:
    ManberMyers(std::string str) : str(str), n(str.size()) {
        sa.resize(n);
        group.resize(n);
        lcp.resize(n-1);
        initSuffixArray();
        initLCP();
    }

    const std::vector<int>& getSuffixArray() const {
        return sa;
    }

    const std::vector<int>& getLCP() const {
        return lcp;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string str;
    std::cin >> str;
    ManberMyers manber(str);

    for (int sa : manber.getSuffixArray()) {
        std::cout << sa+1 << " ";
    }
    std::cout << "\nx ";
    for (int lcp : manber.getLCP()) {
        std::cout << lcp << " ";
    }

    return 0;
}