#include <functional>
#include <vector>
#include <cmath>
#include <iostream>
#include <tuple>

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
        start = std::max(0, start);
        end = std::min(int(tree.size())-2, end);
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

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    const int SQRT = int(std::sqrt(n)) + 1;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int q;
    std::cin >> q;
    using Query = std::tuple<int, int, int>;
    std::vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        l--; r--;
        queries[i] = {l, r, i};
    }

    std::sort(queries.begin(), queries.end(), [=](const Query& q1, const Query& q2) {
        auto [l1, r1, i1] = q1;
        auto [l2, r2, i2] = q2;
        int g1 = r1/SQRT;
        int g2 = r2/SQRT;
        if (g1 != g2) {
            return g1 < g2;
        }
        return l1 < l2;
    });

    FenwickTree<Long> bucket(*std::max_element(arr.begin(), arr.end())+1);
    std::pair<int, int> curr = { 0, 0 };
    bucket.update(arr[0], 1);
    Long validPairs = 0;
    std::vector<Long> answer(q);

    for (auto [ql, qr, qi] : queries) {
        while (curr.second < qr) {
            curr.second++;
            validPairs += bucket.query(arr[curr.second]-k, arr[curr.second]+k);
            bucket.update(arr[curr.second], 1);
        }
        while (ql < curr.first) {
            curr.first--;
            validPairs += bucket.query(arr[curr.first]-k, arr[curr.first]+k);
            bucket.update(arr[curr.first], 1);
        }

        while (qr < curr.second) {
            bucket.update(arr[curr.second], -1);
            validPairs -= bucket.query(arr[curr.second]-k, arr[curr.second]+k);
            curr.second--;
        }
        while (curr.first < ql) {
            bucket.update(arr[curr.first], -1);
            validPairs -= bucket.query(arr[curr.first]-k, arr[curr.first]+k);
            curr.first++;
        }

        answer[qi] = validPairs;
    }

    for (Long ans : answer) {
        std::cout << ans << "\n";
    }

    return 0;
}