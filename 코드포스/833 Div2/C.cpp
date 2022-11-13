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
#include <cassert>

#if __has_include(<ext/pb_ds/assoc_container.hpp>) && __has_include(<ext/pb_ds/tree_policy.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using OrderedSet = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

using Long = long long;
using BigInt = __int128_t;

template<typename T>
struct IsContainer {
    typedef typename std::remove_const<T>::type PlainType;

    template<typename A>
    static constexpr bool test(
        A * pt,
        decltype(pt->begin()) * = nullptr,
        decltype(pt->end()) * = nullptr
    ) { return true; }

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

template<typename TensorType, size_t Dim>
struct TensorElementType {
	typedef typename TensorElementType<TensorType, Dim-1>::type Inner;
	typedef typename Inner::value_type type;
};

template<typename TensorType>
struct TensorElementType<TensorType, 1> {
	typedef typename TensorType::value_type type;
};

template<
	typename TensorType,
	typename FirstIdx,
	typename... RestIdxs,
	typename T = typename TensorElementType<TensorType, sizeof...(RestIdxs)+1>::type>
T& getFromTensor(TensorType& tensor, FirstIdx firstIdx, RestIdxs... restIdxs) {
	constexpr size_t RestCount = sizeof...(restIdxs);
	if constexpr (RestCount == 0) {
		return tensor[firstIdx];
	} else {
		return getFromTensor(tensor[firstIdx], restIdxs...);
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

template<size_t ParamsCnt, typename = std::make_index_sequence<ParamsCnt>>
struct DPFuncGen {};

template<size_t ParamsCnt, size_t... S>
struct DPFuncGen<ParamsCnt, std::index_sequence<S...>> {
	typedef std::function<std::size_t(decltype(S)...)> type;
};

template<
	typename T,
	typename... DimArgs>
class Memo {
private:
	using FuncType = typename DPFuncGen<sizeof...(DimArgs)>::type;
	Tensor<sizeof...(DimArgs), T> dp;
	T undefVal;
	FuncType naive;

public:
	Memo(T undefVal, DimArgs... dargs) : undefVal(undefVal) {
		dp = createTensor(undefVal, dargs...);
	}

	T operator()(DimArgs... args) {
		T& result = getFromTensor(dp, args...);
		if (result != undefVal) {
			return result;
		}
		return result = naive(args...);
	}

	void operator=(const FuncType& newNaive) {
		naive = newNaive;
	}
};

struct IO {
    IO() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
        std::cout.precision(std::numeric_limits<double>::digits10);
    }

    template<typename T>
    T next() {
        T result;
        std::cin >> result;
        return result;
    }

    size_t nextSize() { return next<size_t>(); }
    int nextInt() { return next<int>(); }
    Long nextLong() { return next<Long>(); }
    double nextDouble() { return next<double>(); }
    std::string nextToken() { return next<std::string>(); }

    template<typename T>
    std::vector<T> nexts(size_t n, size_t leftPadding = 0) {
        std::vector<T> arr(leftPadding + n);
        for (auto i = leftPadding; i < arr.size(); ++i) {
            arr[i] = next<T>();
        }
        return arr;
    }

    std::vector<int> nextInts(size_t n, size_t leftPadding = 0) { return nexts<int>(n, leftPadding); }
    std::vector<Long> nextLongs(size_t n, size_t leftPadding = 0) { return nexts<Long>(n, leftPadding); }
    std::vector<double> nextDoubles(size_t n, size_t leftPadding = 0) { return nexts<double>(n, leftPadding); }
    std::vector<std::string> nextTokens(size_t n, size_t leftPadding = 0) { return nexts<std::string>(n, leftPadding); }

    template<typename T, size_t N>
    std::array<T, N> nexts() {
        std::array<T, N> result;
        for (auto& val : result) {
            val = next<T>();
        }
        return result;
    }

    Tensor<2, Long> nextMatrix(size_t r, size_t c) {
        Tensor<2, Long> result(r, std::vector<Long>(c));
        for (size_t i = 0; i < r; ++i) {
            result[i] = nextLongs(c);
        }
        return result;
    }

    Tensor<2, size_t> nextGraph(size_t n, size_t m) {
        Tensor<2, size_t> result(n+1);
        for (size_t i = 0; i < m; ++i) {
            auto [u, v] = nexts<size_t, 2>();
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

    void printYes(bool yes, bool bold = false) {
        if (bold) {
            println(yes ? "YES" : "NO");
        } else {
            println(yes ? "Yes" : "No");
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
            // For partial scores:
            std::cout.flush();
        }
    }
} io;

int main() {
    io.codeforces([&]() {
        int n = io.nextInt();
        auto arr = io.nextLongs(n);

        auto sum = arr;
        for (int i = 1; i < arr.size(); ++i) {
            sum[i] += sum[i-1];
        }

        std::vector<int> zeroPos;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 0) {
                zeroPos.push_back(i);
            }
        }
        zeroPos.push_back(n);

        int answer = 0;
        for (int zi = 0; zi+1 < zeroPos.size(); ++zi) {
            int pos = zeroPos[zi];
            std::map<Long, int> count;
            for (int i = pos; i < zeroPos[zi+1]; ++i) {
                count[sum[i]]++;
            }
            int maxCount = INT32_MIN;
            for (auto [_, cnt] : count) {
                maxCount = std::max(maxCount, cnt);
            }
            answer += maxCount;
        }

        for (int i = 0; i < zeroPos.front(); ++i) {
            if (sum[i] == 0) {
                answer++;
            }
        }

        io.println(answer);
    });
    
    return 0;
}