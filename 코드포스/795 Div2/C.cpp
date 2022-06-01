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
    void write(T value) {
        std::cout << value << " ";
    }

    template<typename T, typename... Args>
    void write(T value, Args... args) {
        std::cout << value << " ";
        write(args...);
    }

    void writeLine() {
        std::cout << "\n";
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

int getScore(std::string s) {
    int sum = 0;
    for (int i = 0; i+1 < s.size(); ++i) {
        sum += 10*(s[i]-'0') + (s[i+1]-'0');
    }
    return sum;
}

int main() {
    IO io;
    io.codeforces([&]() {
        int n = io.readInt();
        int k = io.readInt();
        auto s = io.readToken();
        int score = getScore(s);
        
        if (score == 0 || k == 0) {
            io.writeLine(score);
            return;
        }

        if (n == 2) {
            io.writeLine(std::min(10*(s[0]-'0') + (s[1]-'0'), 10*(s[1]-'0') + (s[0]-'0')));
            return;
        }

        int firstOne = s.find_first_of("1");
        int firstDist = firstOne;
        int lastOne = s.find_last_of("1");
        int lastDist = s.size()-1-lastOne;

        if (lastOne == firstOne) {
            if (lastOne == 0) {
                if (lastDist <= k) {
                    score -= 9;
                }
            } else if (lastOne == n-1) {
                // do nothing
            } else {
                if (lastDist <= k) {
                    score -= 10;
                } else if (firstDist <= k) {
                    score -= 1;
                }
            }
        } else {
            if (lastDist > 0 && k >= lastDist) {
                k -= lastDist;
                score -= 10;
            }
            if (firstDist > 0 && k >= firstDist) {
                k -= firstDist;
                score -= 1;
            }
        }

        io.writeLine(score);
    });
    
    return 0;
}