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
        println(yes ? "YES" : "NO");
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

std::vector<int> getFail(std::string& str) {
    std::vector<int> fail(str.size(), 0);
    for (int i = 1, j = 0; i < (int)str.size(); ++i) {
        while (j > 0 && str[i] != str[j]) {
            j = fail[j-1];
        }
        if (str[i] == str[j]) {
            fail[i] = ++j;
        }
    }
    return fail;
}

std::vector<int> KMP(std::string& para, std::string& target) {
    std::vector<int> fail = getFail(target);
    std::vector<int> found;

    for (int i = 0, j = 0; i < (int)para.size(); ++i) {
        while (j > 0 && para[i] != target[j]) {
            j = fail[j-1];
        }
        if (para[i] == target[j]) {
            if (j == (int)target.size()-1) {
                found.push_back(i-target.size()+1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
    return found;
}

int main() {
    io.samsung([&]() {
        auto [n, m] = io.nexts<int, 2>();
        auto s = io.nextToken();
        auto t = io.nextToken();

        auto getCountVector = [](const std::string& str) {
            Tensor<2, int> result = createTensor(0, 2, str.size());
            result[str[0]-'a'][0] = 1;
            for (int i = 1; i < str.size(); ++i) {
                int curr = str[i]-'a';
                result[curr][i] = result[curr][i-1] + 1;
                result[!curr][i] = result[!curr][i-1];
            }
            return result;
        };

        auto sCnt = getCountVector(s);
        auto tCnt = getCountVector(t);

        int originStart;
        for (originStart = 0; originStart < m; ++originStart) {
            if (tCnt[0][originStart] && tCnt[1][originStart]) {
                break;
            }
        }
        if (originStart == m) {
            io.printYes(tCnt[t[0]-'a'].back() <= sCnt[t[0]-'a'].back());
            return;
        }
        int originEnd;
        for (originEnd = m-1; originEnd >= originStart; --originEnd) {
            if (tCnt[0].back()-tCnt[0][originEnd-1] && tCnt[1].back()-tCnt[1][originEnd-1]) {
                break;
            }
        }
        if (originStart > originEnd) {
            int leftChr = t.front()-'a';
            int leftCnt = tCnt[leftChr].back();
            int rightChr = t.back()-'a';
            int rightCnt = tCnt[rightChr].back();
            
            for (int i = 1; i+1 < n; ++i) {
                if (leftCnt <= sCnt[leftChr][i] && rightCnt <= sCnt[rightChr].back()-sCnt[rightChr][i]) {
                    io.printYes(true);
                    return;
                }
            }
            io.printYes(false);
            return;
        }

        std::string origin = t.substr(originStart, originEnd-originStart+1);
        auto pos = KMP(s, origin);
        
        for (int p : pos) {
            bool success = true;
            // check left
            int leftChr = t[originStart-1]-'a';
            if ((p == 0 ? 0 : sCnt[leftChr][p-1]) < tCnt[leftChr][originStart-1]) {
                success = false;
            }
            // check right
            int rightChr = t[originEnd+1]-'a';
            if (sCnt[rightChr].back()-sCnt[rightChr][p+origin.size()-1] < tCnt[rightChr].back()-tCnt[rightChr][originEnd]) {
                success = false;
            }

            if (success) {
                io.printYes(true);
                return;
            }
        }
        io.printYes(false);
    });
    
    return 0;
}