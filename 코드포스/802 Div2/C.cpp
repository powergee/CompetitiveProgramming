#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <array>
#include <queue>
#include <map>
#include <set>
#include <cmath>

using Long = long long;
using BigInt = __int128_t;

template <size_t Dim, typename T>
struct TensorTemp {
    typedef std::vector<typename TensorTemp<Dim-1, T>::type> type;
};

template<typename T>
struct TensorTemp<1, T>  {
    typedef T type;
};

template <size_t Dim, typename T>
using Tensor = std::vector<typename TensorTemp<Dim, T>::type>;

template<typename T, typename FirstDim, typename... RestDims>
Tensor<sizeof...(RestDims)+1, T> createTensor(T init, FirstDim firstDim, RestDims... restDims) {
    constexpr size_t DimCount = sizeof...(restDims)+1;
    if constexpr (DimCount > 1) {
        return Tensor<DimCount, T>(firstDim, createTensor<T>(init, restDims...));
    } else {
        return Tensor<DimCount, T>(firstDim, init);
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const &vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << (it == vec.begin() ? "" : " ") << *it;
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::set<T> const &vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << (it == vec.begin() ? "" : " ") << *it;
    }
    return os;
}

struct IO {
    IO() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
    }

    template<typename T>
    T scan() {
        T result;
        std::cin >> result;
        return result;
    }

    int scanInt() { return scan<int>(); }
    Long scanLong() { return scan<Long>(); }
    double scanDouble() { return scan<double>(); }
    std::string scanToken() { return scan<std::string>(); }

    template<typename T>
    std::vector<T> scans(int n, int leftPadding = 0) {
        std::vector<T> arr(leftPadding + n);
        for (int i = leftPadding; i < arr.size(); ++i) {
            arr[i] = scan<T>();
        }
        return arr;
    }

    std::vector<int> scanInts(int n, int leftPadding = 0) { return scans<int>(n, leftPadding); }
    std::vector<Long> scanLongs(int n, int leftPadding = 0) { return scans<Long>(n, leftPadding); }
    std::vector<double> scanDoubles(int n, int leftPadding = 0) { return scans<double>(n, leftPadding); }
    std::vector<std::string> scanTokens(int n, int leftPadding = 0) { return scans<std::string>(n, leftPadding); }

    template<typename T, unsigned int N>
    std::array<T, N> scans() {
        std::array<T, N> result;
        for (int i = 0; i < N; ++i) {
            result[i] = scanInt();
        }
        return result;
    }

    template<unsigned int N> std::array<int, N> scanInts() { return scans<int, N>(); }
    template<unsigned int N> std::array<Long, N> scanLongs() { return scans<Long, N>(); }
    template<unsigned int N> std::array<double, N> scanDoubles() { return scans<double, N>(); }
    template<unsigned int N> std::array<std::string, N> scanTokens() { return scans<std::string, N>(); }

    std::vector<std::vector<int>> scanMatrix(int r, int c) {
        std::vector<std::vector<int>> result(r, std::vector<int>(c));
        for (int i = 0; i < r; ++i) {
            result[i] = scanInts(c);
        }
        return result;
    }

    template<typename T>
    void print(T value) {
        std::cout << value << " ";
    }

    template<typename T, typename... Args>
    void print(T value, Args... args) {
        print(value);
        print(args...);
    }

    void println() {
        std::cout << "\n";
    }

    template<typename T>
    void println(T value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void println(T value, Args... args) {
        std::cout << value << " ";
        println(args...);
    }

    void printYes(bool yes) {
        println(yes ? "Yes" : "No");
    }

    void untilEOF(std::function<void()> solve) {
        while (std::cin.eof() != false) {
            solve();
        }
    }

    void codeforces(std::function<void()> solve) {
        int T = scanInt();
        while (T--) {
            solve();
        }
    }

    void google(std::function<void()> solve) {
        int T = scanInt();
        for (int t = 1; t <= T; ++t) {
            std::cout << "Case #" << t << ": ";
            solve();
        }
    }
};

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::vector<T> lazy;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

    void propagate(int index, int start, int end) {
        if (lazy[index]) {
            tree[index] += lazy[index] * (end-start+1);
            if (start < end) {
                lazy[index*2] += lazy[index];
                lazy[index*2+1] += lazy[index];
            }
            lazy[index] = 0;
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return query(index*2, reqStart, reqEnd, treeStart, treeMed)
                 + query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
        } else {
            return 0;
        }
    }

    void update(T add, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] += add;
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqStart, reqEnd, treeStart, treeMed);
            update(add, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

public:
    SegTree(const std::vector<T>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
        initialize(1, 0, originCount-1, original);
    }

    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, T add) {
        update(add, 1, start, end, 0, originCount-1);
    }
};

int main() {
    IO io;
    io.codeforces([&]() {
        int n = io.scanInt();
        auto arr = io.scanLongs(n);
        SegTree<Long> tree(arr);
        Long sum = 0;

        for (int i = 0; i+1 < n; ++i) {
            Long curr = tree.query(i, i);
            Long next = tree.query(i+1, i+1);
            
            if (curr > next) {
                tree.update(0, i, next-curr);
                sum += std::abs(next-curr);
            } else if (curr < next) {
                tree.update(i, n-1, curr-next);
                sum += std::abs(next-curr);
            }
        }
        io.println(sum + std::abs(tree.query(n-1, n-1)));
    });
    
    return 0;
}