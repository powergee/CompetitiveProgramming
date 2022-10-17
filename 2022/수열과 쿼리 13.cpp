#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <optional>

using Long = long long;
const Long MOD = 1000000007;

class SegTree {
private:
    int originCount;
    std::vector<Long> tree;
    std::vector<std::optional<std::pair<Long, Long>>> lazy;
    
    void initialize(int index, int start, int end, const std::vector<Long>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = (tree[index*2] + tree[index*2+1]) % MOD;
        }
    }

    void propagate(int index, int start, int end) {
        if (lazy[index].has_value()) {
            auto [coeff, constant] = lazy[index].value();
            tree[index] = ((tree[index]*coeff%MOD) + ((end-start+1)*constant)%MOD) % MOD;
            if (start < end) {
                if (lazy[index*2].has_value()) {
                    auto [subCoeff, subConstant] = lazy[index*2].value();
                    lazy[index*2] = std::make_pair(coeff*subCoeff%MOD, (coeff*subConstant+constant)%MOD);
                } else {
                    lazy[index*2] = lazy[index].value();
                }
                if (lazy[index*2+1].has_value()) {
                    auto [subCoeff, subConstant] = lazy[index*2+1].value();
                    lazy[index*2+1] = std::make_pair(coeff*subCoeff%MOD, (coeff*subConstant+constant)%MOD);
                } else {
                    lazy[index*2+1] = lazy[index].value();
                }
            }
            lazy[index] = std::nullopt;
        }
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

    void apply(int index, int reqStart, int reqEnd, int treeStart, int treeEnd, Long coeff, Long constant) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] = std::make_pair(coeff, constant);
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            apply(index*2, reqStart, reqEnd, treeStart, treeMed, coeff, constant);
            apply(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd, coeff, constant);
            tree[index] = (tree[index*2] + tree[index*2+1]) % MOD;
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
    }

    SegTree(const std::vector<Long>& original) : SegTree(original.size()) {
        initialize(1, 0, originCount-1, original);
    }

    Long query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void apply(int start, int end, Long coeff, Long constant) {
        apply(1, start, end, 0, originCount-1, coeff%MOD, constant%MOD);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    SegTree tree(arr);

    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;
        switch (op)
        {
            case 1: {
                Long x, y, v;
                std::cin >> x >> y >> v;
                tree.apply(x-1, y-1, 1, v);
                break;
            }
            case 2: {
                Long x, y, v;
                std::cin >> x >> y >> v;
                tree.apply(x-1, y-1, v, 0);
                break;
            }
            case 3: {
                Long x, y, v;
                std::cin >> x >> y >> v;
                tree.apply(x-1, y-1, 0, v);
                break;
            }
            case 4: {
                Long x, y;
                std::cin >> x >> y;
                std::cout << tree.query(x-1, y-1) << "\n";
                break;
            }
        }
    }

    return 0;
}