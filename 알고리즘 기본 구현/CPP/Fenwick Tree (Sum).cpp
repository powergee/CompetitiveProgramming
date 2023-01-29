#include <vector>

using Long = long long;

template <typename T>
class FenwickTree {
private:
    std::vector<T> tree;

public:
    T query(int end) {
        T result = 0;
        while (end > 0) {
            result += tree[end];
            end -= (end & -end);
        }
        return result;
    }

    void update(int pos, T add) {
        while (pos < int(tree.size())) {
            tree[pos] += add;
            pos += (pos & -pos);
        }
    }

    T query(int start, int end) {
        return query(end) - query(start-1);
    }

    FenwickTree(int count) {
        tree.resize(count+1, 0);
    }

    FenwickTree(const std::vector<T>& original) : FenwickTree(original.size()) {
        for (int i = 0; i < int(original.size()); ++i) {
            update(i+1, original[i]);
        }
    }
};