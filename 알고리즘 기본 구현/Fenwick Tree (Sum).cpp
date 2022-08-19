#include <vector>

using Long = long long;

template <typename T>
class FenwickTree {
private:
    std::vector<T> tree;

    T query(int end) {
        T result = 0;
        while (end > 0) {
            result += tree[end];
            end -= (end & -end);
        }
        return result;
    }

public:
    // Note: pos must be 0-indexed.
    void update(int pos, T add) {
        pos++;
        while (pos < tree.size()) {
            tree[pos] += add;
            pos += (pos & -pos);
        }
    }

    // Note: start and end must be 0-indexed.
    T query(int start, int end) {
        return query(end+1) - query(start);
    }

    FenwickTree(int count) {
        tree.resize(count+1, 0);
    }

    // Note: original must be 0-indexed.
    FenwickTree(const std::vector<T>& original) : FenwickTree(original.size()) {
        for (int i = 0; i < original.size(); ++i) {
            update(i, original[i]);
        }
    }
};