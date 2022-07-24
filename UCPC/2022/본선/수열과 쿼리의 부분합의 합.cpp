#include <iostream>
#include <vector>
#include <cmath>
#define MOD 998244353LL

typedef long long Long;

Long n;
std::vector<Long> squareSum, naiveSum;

Long getSum(std::vector<Long>& sum, int l, int r) {
    if (l == 0) {
        return sum[r];
    }
    return (sum[r] - sum[l-1] + MOD) % MOD;
}

struct Query {
    Long c, qIdx;
};

class SegTree {
private:
    int originCount;
    std::vector<Long> tree;
    std::vector<Query> lazy;

    void propagate(int index, int start, int end) {
        if (lazy[index].c != -1) {
            auto [c, qIdx] = lazy[index];
            Long coeff = ((n-1)*getSum(naiveSum, start, end) - getSum(squareSum, start, end) + (end-start+1)*n + MOD) % MOD;
            tree[index] = ((c * (qIdx+1) % MOD) * coeff) % MOD;
            if (start < end) {
                lazy[index*2] = lazy[index];
                lazy[index*2+1] = lazy[index];
            }
        }
        lazy[index] = { -1, -1 };
    }

    Long query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return (query(index*2, reqStart, reqEnd, treeStart, treeMed)
                  + query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd)) % MOD;
        } else {
            return 0;
        }
    }

    void update(Query q, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] = q;
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(q, index*2, reqStart, reqEnd, treeStart, treeMed);
            update(q, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = (tree[index*2] + tree[index*2+1]) % MOD;
        }
    }

public:
    SegTree(int n) {
        originCount = n;
        int treeHeight = (int)std::ceil((float)log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize, 0);
        lazy.resize(vecSize, { -1, -1 });
    }

    Long query(int start, int end) {
        if (start > end) {
            return 0;
        }
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, Query q) {
        if (start > end) {
            return;
        }
        update(q, 1, start, end, 0, originCount-1);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Long q;
    std::cin >> n >> q;

    squareSum.resize(n+1, 0);
    naiveSum.resize(n+1, 0);
    for (Long i = 1; i < squareSum.size(); ++i) {
        squareSum[i] = (i*i + squareSum[i-1]) % MOD;
        naiveSum[i] = (i + naiveSum[i-1]) % MOD;
    }

    Long answer = 0;
    SegTree stree(n);

    for (Long qIdx = 0; qIdx < q; ++qIdx) {
        Long l, r, c;
        std::cin >> l >> r >> c;
        --l; --r;
    
        Long coeff = ((n-1)*getSum(naiveSum, l, r) - getSum(squareSum, l, r) + (r-l+1)*n + MOD) % MOD;
        answer += ((coeff * c) % MOD) * (qIdx+1);
        answer %= MOD;

        answer += stree.query(0, l-1) + stree.query(r+1, n-1);
        answer %= MOD;

        stree.update(l, r, { c, qIdx });
    }

    std::cout << answer;

    return 0;
}