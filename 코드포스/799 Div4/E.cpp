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

int main() {
    IO io;
    io.codeforces([&]() {
        auto [n, s] = io.scans<int, 2>();
        auto arr = io.scanInts(n, 1);
        if (std::accumulate(arr.begin()+1, arr.end(), 0) < s) {
            io.println(-1);
            return;
        }

        std::vector<int> sum(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + arr[i];
        }

        int answer = INT32_MAX;
        for (int i = 1; i <= n; ++i) {
            auto found = std::upper_bound(sum.begin()+i, sum.end(), s+sum[i-1]);
            found = std::prev(found);
            if (*found-sum[i-1] == s) {
                answer = std::min(answer, n-int(found-sum.begin() - i + 1));
            }
        }

        io.println(answer == INT32_MAX ? -1 : answer);
    });
    
    return 0;
}