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

template<typename T>
struct IsContainer {
    typedef typename std::remove_const<T>::type PlainType;

    template<typename A>
    static constexpr bool test(
        A * pt,
        A const * cpt = nullptr,
        decltype(pt->begin()) * = nullptr,
        decltype(pt->end()) * = nullptr,
        decltype(cpt->begin()) * = nullptr,
        decltype(cpt->end()) * = nullptr,
        typename A::iterator * pi = nullptr,
        typename A::const_iterator * pci = nullptr) {

        typedef typename A::iterator iterator;
        typedef typename A::const_iterator const_iterator;
        return std::is_same<decltype(pt->begin()), iterator>::value &&
            std::is_same<decltype(pt->end()), iterator>::value &&
            std::is_same<decltype(cpt->begin()), const_iterator>::value &&
            std::is_same<decltype(cpt->end()), const_iterator>::value;
    }

    template<typename A>
    static constexpr bool test(...) { return false; }

    static constexpr bool value = test<PlainType>(nullptr);
};

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

template<
    typename T,
    typename = std::enable_if_t<IsContainer<T>::value>,
    typename = std::enable_if_t<!std::is_same<T, std::string>::value>>
std::ostream& operator<<(std::ostream& os, const T &cont) {
    for (auto it = cont.begin(); it != cont.end(); ++it) {
        std::cout << (it == cont.begin() ? "" : " ") << *it;
    }
    return os;
}

template<
    typename ContType,
    typename MapFunc,
    typename = std::enable_if_t<IsContainer<ContType>::value>,
    typename ElemType = typename ContType::value_type>
auto map(const ContType& cont, const MapFunc& func) {
    typedef decltype(func(*cont.begin())) RetType;
    std::vector<RetType> result;
    for (auto v : cont) {
        result.push_back(func(v));
    }
    return result;
}

template<
    typename ContType,
    typename = std::enable_if_t<IsContainer<ContType>::value>,
    typename ElemType = typename ContType::value_type>
std::map<ElemType, int> countElements(const ContType& cont) {
    std::map<ElemType, int> count;
    for (auto v : cont) {
        count[v]++;
    }
    return count;
}

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::pair<Ts...> const &p) {
    std::cout << p.first << " " << p.second;
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
            result[i] = scan<T>();
        }
        return result;
    }

    template<unsigned int N> std::array<int, N> scanInts() { return scans<int, N>(); }
    template<unsigned int N> std::array<Long, N> scanLongs() { return scans<Long, N>(); }
    template<unsigned int N> std::array<double, N> scanDoubles() { return scans<double, N>(); }
    template<unsigned int N> std::array<std::string, N> scanTokens() { return scans<std::string, N>(); }

    Tensor<2, int> scanMatrix(int r, int c) {
        Tensor<2, int> result(r, std::vector<int>(c));
        for (int i = 0; i < r; ++i) {
            result[i] = scanInts(c);
        }
        return result;
    }

    Tensor<2, int> scanTree(int n) {
        Tensor<2, int> result(n+1);
        for (int i = 0; i < n-1; ++i) {
            auto [u, v] = scans<int, 2>();
            result[u].push_back(v);
            result[v].push_back(u);
        }
        return result;
    }

    template<typename T>
    void print(const T& value) {
        std::cout << value << " ";
    }

    template<typename T, typename... Args>
    void print(const T& value, Args... args) {
        print(value);
        print(args...);
    }

    void println() {
        std::cout << "\n";
    }

    template<typename T>
    void println(const T& value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void println(const T& value, Args... args) {
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
} io;

int main() {
    io.codeforces([&]() {
        auto [n, m] = io.scans<int, 2>();
        auto mat = io.scanMatrix(n, m);

        int max = INT32_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                max = std::max(max, mat[i][j]);
            }
        }
        int answer = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == max) {
                    answer = std::max(i+1, n-i) * std::max(j+1, m-j);
                }
            }
        }
        io.println(answer);
    });
    
    return 0;
}