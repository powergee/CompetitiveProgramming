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
        std::cout << value << " ";
        print(args...);
    }

    void printLine() {
        std::cout << "\n";
    }

    template<typename T>
    void printLine(T value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void printLine(T value, Args... args) {
        std::cout << value << " ";
        printLine(args...);
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
        auto tokens = io.scanTokens(2*n+1);

        std::set<char> cands;
        int count[26] = {0};
        for (auto t : tokens) {
            if (t.size() == 1) {
                cands.insert(t[0]);
            }
            std::set<int> appeared;
            for (char c : t) {
                count[c-'a']++;
            }
        }

        char answer = 0;
        for (char c : cands) {
            if (count[c-'a'] % 2) {
                answer = c;
            }
        }

        if (answer == 0) {
            exit(1);
        } else {
            io.printLine(answer);
        }
    });
    
    return 0;
}