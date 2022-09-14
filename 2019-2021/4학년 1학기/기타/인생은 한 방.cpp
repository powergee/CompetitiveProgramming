#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <array>
#include <queue>
#include <map>

using Long = long long;
using BigInt = __int128_t;

struct IO {
    IO() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
    }

    template<typename T>
    T read() {
        T result;
        std::cin >> result;
        return result;
    }

    int readInt() { return read<int>(); }
    Long readLong() { return read<Long>(); }
    double readDouble() { return read<double>(); }
    std::string readToken() { return read<std::string>(); }

    template<typename T>
    std::vector<T> reads(int n) {
        std::vector<T> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = read<T>();
        }
        return arr;
    }

    std::vector<int> readInts(int n) { return reads<int>(n); }
    std::vector<Long> readLongs(int n) { return reads<Long>(n); }
    std::vector<double> readDoubles(int n) { return reads<double>(n); }
    std::vector<std::string> readTokens(int n) { return reads<std::string>(n); }

    template<typename T, unsigned int N>
    std::array<T, N> reads() {
        std::array<T, N> result;
        for (int i = 0; i < N; ++i) {
            result[i] = readInt();
        }
        return result;
    }

    template<unsigned int N> std::array<int, N> readInts() { return reads<int, N>(); }
    template<unsigned int N> std::array<Long, N> readLongs() { return reads<Long, N>(); }
    template<unsigned int N> std::array<double, N> readDoubles() { return reads<double, N>(); }
    template<unsigned int N> std::array<std::string, N> readTokens() { return reads<std::string, N>(); }

    std::vector<std::vector<int>> readMatrix(int r, int c) {
        std::vector<std::vector<int>> result(r, std::vector<int>(c));
        for (int i = 0; i < r; ++i) {
            result[i] = readInts(c);
        }
        return result;
    }

    template<typename T>
    void writeLine(T value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void writeLine(T value, Args... args) {
        std::cout << value << " ";
        writeLine(args...);
    }

    void codeforces(std::function<void()> solve) {
        int T = readInt();
        while (T--) {
            solve();
        }
    }

    void google(std::function<void()> solve) {
        int T = readInt();
        for (int t = 1; t <= T; ++t) {
            std::cout << "Case #" << t << ": ";
            solve();
        }
    }
};

int main() {
    IO io;
    int n = io.readInt();
    auto word = io.readToken();

    bool yes = false;
    for (int i = 0; i+4 < n; ++i) {
        bool satisfied = true;
        for (int j = 0; j < 4; ++j) {
            if (std::abs(word[i+j]-word[i+j+1]) != 1) {
                satisfied = false;
            }
        }
        yes = yes || satisfied;
    }

    io.writeLine(yes ? "YES" : "NO");
    
    return 0;
}