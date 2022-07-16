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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using OrderedSet = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    T next() {
        T result;
        std::cin >> result;
        return result;
    }

    int nextInt() { return next<int>(); }
    Long nextLong() { return next<Long>(); }
    double nextDouble() { return next<double>(); }
    std::string nextToken() { return next<std::string>(); }

    template<typename T>
    std::vector<T> nexts(int n, int leftPadding = 0) {
        std::vector<T> arr(leftPadding + n);
        for (int i = leftPadding; i < arr.size(); ++i) {
            arr[i] = next<T>();
        }
        return arr;
    }

    std::vector<int> nextInts(int n, int leftPadding = 0) { return nexts<int>(n, leftPadding); }
    std::vector<Long> nextLongs(int n, int leftPadding = 0) { return nexts<Long>(n, leftPadding); }
    std::vector<double> nextDoubles(int n, int leftPadding = 0) { return nexts<double>(n, leftPadding); }
    std::vector<std::string> nextTokens(int n, int leftPadding = 0) { return nexts<std::string>(n, leftPadding); }

    template<typename T, unsigned int N>
    std::array<T, N> nexts() {
        std::array<T, N> result;
        for (int i = 0; i < N; ++i) {
            result[i] = next<T>();
        }
        return result;
    }

    template<unsigned int N> std::array<int, N> nextInts() { return nexts<int, N>(); }
    template<unsigned int N> std::array<Long, N> nextLongs() { return nexts<Long, N>(); }
    template<unsigned int N> std::array<double, N> nextDoubles() { return nexts<double, N>(); }
    template<unsigned int N> std::array<std::string, N> nextTokens() { return nexts<std::string, N>(); }

    Tensor<2, int> nextMatrix(int r, int c) {
        Tensor<2, int> result(r, std::vector<int>(c));
        for (int i = 0; i < r; ++i) {
            result[i] = nextInts(c);
        }
        return result;
    }

    Tensor<2, int> nextTree(int n) {
        Tensor<2, int> result(n+1);
        for (int i = 0; i < n-1; ++i) {
            auto [u, v] = nexts<int, 2>();
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
        int T = nextInt();
        while (T--) {
            solve();
        }
    }

    void google(std::function<void()> solve) {
        int T = nextInt();
        for (int t = 1; t <= T; ++t) {
            std::cout << "Case #" << t << ": ";
            solve();
        }
    }

    void samsung(std::function<void()> solve) {
        int T = nextInt();
        for (int t = 1; t <= T; ++t) {
            std::cout << "Case #" << t << "\n";
            solve();
            std::cout.flush();
        }
    }
} io;

const Long MAX = 500001;
const Long MOD = 1000000007;

Long factorial(Long n) {
    static std::vector<Long> dp(MAX+1, -1);
    if (n == 0) {
        return 1;
    } else if (dp[n] != -1) {
        return dp[n];
    }
    return dp[n] = (factorial(n-1) * n) % MOD;
}

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

Long getModInverse(Long val) {
    return getModPow(val, MOD-2);
}

Long getComb(Long n, Long k) {
    if (n < k) {
        return 0;
    } else if (n == k) {
        return 1;
    }
    return (factorial(n) * getModInverse((factorial(n-k)*factorial(k)) % MOD)) % MOD;
}

int main() {
    io.samsung([&]() {
        auto [n, k] = io.nexts<int, 2>();
        auto arr = io.nextLongs(n);

        io.println([&]() -> Long {
            Long total = std::accumulate(arr.begin(), arr.end(), 0LL);
            if (total % k) {
                return 0;
            }
            Long perSeg = total / k;

            if (perSeg == 0) {
                Long window = 0, count = 0;
                bool dirty = false;
                for (int i = 0; i < n; ++i) {
                    window += arr[i];
                    dirty = true;
                    if (window == 0) {
                        count++;
                        window = 0;
                        dirty = false;
                    }
                }
                if (dirty) {
                    return 0;
                }
                return getComb(count-1, k-1);
            }

            std::vector<Long> sum = arr;
            std::map<Long, std::vector<Long>> sumInv;
            sumInv[arr[0]].push_back(0);
            for (int i = 1; i < n; ++i) {
                sum[i] = sum[i-1] + arr[i];
                sumInv[sum[i]].push_back(i);
            }

            auto getSum = [&](int left, int right) {
                if (left == 0) {
                    return sum[right];
                } else {
                    return sum[right] - sum[left-1];
                }
            };
            
            std::vector<Long> dp(n, -1);
            std::function<Long(int, int)> countCases = [&](int start, int currStage) -> Long {
                if (start == n) {
                    return 0;
                }
                if (currStage == 0) {
                    return (getSum(start, n-1) == perSeg ? 1 : 0);
                }
                Long& result = dp[start];
                if (result != -1) {
                    return result;
                }

                const auto& endpoints = sumInv[sum[start]-arr[start]+perSeg];
                auto it = std::lower_bound(endpoints.begin(), endpoints.end(), start);
                result = 0;
                while (it != endpoints.end()) {
                    result += countCases(*it+1, currStage-1);
                    result %= MOD;
                    it++;
                }
                return result;
            };
            return countCases(0, k-1);
        }());
    });
    
    return 0;
}