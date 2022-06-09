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

template<typename T, size_t FirstDim, size_t... RestDims>
Tensor<sizeof...(RestDims)+1, T> createTensor(T init) {
    constexpr size_t DimCount = sizeof...(RestDims)+1;
    if constexpr (DimCount > 1) {
        return Tensor<DimCount, T>(FirstDim, createTensor<T, RestDims...>(init));
    } else {
        return Tensor<DimCount, T>(FirstDim, init);
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
    std::vector<T> scans(int n) {
        std::vector<T> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = scan<T>();
        }
        return arr;
    }

    std::vector<int> scanInts(int n) { return scans<int>(n); }
    std::vector<Long> scanLongs(int n) { return scans<Long>(n); }
    std::vector<double> scanDoubles(int n) { return scans<double>(n); }
    std::vector<std::string> scanTokens(int n) { return scans<std::string>(n); }

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
        auto [n, k] = io.scans<int, 2>();
        auto arr = io.scanInts(n);

        Long profit = 0;
        std::vector<int> count(k, 0); 
        for (int i = 0; i < n; ++i) {
            profit += arr[i] / k;
            count[arr[i] % k]++;
        }

        int i = 1, j = k-1;
        while (i <= j) {
            if (count[j] == 0) {
                --j;
            } else if (count[i] == 0 || i+j < k) {
                ++i;
            } else if (i == j) {
                if (count[i] >= 2) {
                    profit += 1;
                    count[i] -= 2;
                } else {
                    break;
                }
            } else {
                profit += 1;
                count[i] -= 1;
                count[j] -= 1;
            }
        }

        io.println(profit);
    });
    
    return 0;
}