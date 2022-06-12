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
            result[i] = scan<T>();
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
        int n = io.scanInt();
        auto s = io.scanToken();
        auto t = io.scanToken();

        auto digest = [&](std::string& str, std::vector<int>& aSum, std::vector<int>& bSum, std::vector<int>& cSum, std::vector<int>& bPos, std::vector<int>& cPos) {
            aSum[0] = (str[0] == 'a' ? 1 : 0);
            bSum[0] = (str[0] == 'b' ? 1 : 0);
            cSum[0] = (str[0] == 'c' ? 1 : 0);
            if (str[0] == 'b') {
                bPos.push_back(0);
            }
            if (str[0] == 'c') {
                cPos.push_back(0);
            }
            for (int i = 1; i < n; ++i) {
                aSum[i] = aSum[i-1] + (str[i] == 'a' ? 1 : 0);
                bSum[i] = bSum[i-1] + (str[i] == 'b' ? 1 : 0);
                cSum[i] = cSum[i-1] + (str[i] == 'c' ? 1 : 0);
                if (str[i] == 'b') {
                    bPos.push_back(i);
                }
                if (str[i] == 'c') {
                    cPos.push_back(i);
                }
            }
        };

        auto isPossible = [&]() -> bool {
            std::map<char, int> sCnt, tCnt;
            for (int i = 0; i < n; ++i) {
                sCnt[s[i]]++;
                tCnt[t[i]]++;
            }
            if (sCnt != tCnt) {
                return false;
            }

            std::vector<int> s_aSum(n, 0), s_bSum(n, 0), s_cSum(n, 0);
            std::vector<int> s_bPos, s_cPos;
            digest(s, s_aSum, s_bSum, s_cSum, s_bPos, s_cPos);

            std::vector<int> t_aSum(n, 0), t_bSum(n, 0), t_cSum(n, 0);
            std::vector<int> t_bPos, t_cPos;
            digest(t, t_aSum, t_bSum, t_cSum, t_bPos, t_cPos);

            for (int bIndex = 0; bIndex < s_bPos.size(); ++bIndex) {
                int onS = s_bPos[bIndex];
                int onT = t_bPos[bIndex];
                if (s_aSum[onS] < t_aSum[onT]) {
                    return false;
                }
            }

            for (int cIndex = 0; cIndex < s_cPos.size(); ++cIndex) {
                int onS = s_cPos[cIndex];
                int onT = t_cPos[cIndex];
                if (s_bSum[onS] < t_bSum[onT] || s_aSum[onS] != t_aSum[onT]) {
                    return false;
                }
            }

            return true;
        };

        io.printYes(isPossible());
    });
    
    return 0;
}