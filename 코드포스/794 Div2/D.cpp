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

    void writeYes(bool yes) {
        writeLine(yes ? "Yes" : "No");
    }

    void untilEOF(std::function<void()> solve) {
        while (std::cin.eof() != false) {
            solve();
        }
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
    io.codeforces([&]() {
        auto [a, b, c, d] = io.readInts<4>();
        auto s = io.readToken();
        int n = s.size();
        
        std::map<char, int> count;
        for (char ch : s) {
            count[ch]++;
        }

        if (count['A'] != a+c+d || count['B'] != b+c+d) {
            io.writeYes(false);
            return;
        }

        std::vector<std::string> tokens;
        bool looking = false;
        int start = 0;
        s += s.back();
        for (int i = 0; i < n; ++i) {
            if (looking) {
                if (s[i] != s[i+1]) {
                    // do nothing
                } else {
                    auto token = s.substr(start, i-start+1);
                    looking = false;
                    tokens.push_back(token);
                }
            } else {
                if (s[i] != s[i+1]) {
                    start = i;
                    looking = true;
                } else {
                    // do nothing
                }
            }
        }

        std::sort(tokens.begin(), tokens.end(), [](std::string s1, std::string s2) {
            if (s1.size()%2 != s2.size()%2) {
                return s1.size()%2 < s2.size()%2;
            }
            return s1.size() < s2.size();
        });
        for (std::string token : tokens) {
            while (!token.empty()) {
                int* home = token[0] == 'A' ? &c : &d;
                int* away = token[0] == 'B' ? &c : &d;
                if (*home) {
                    int maxEarn = token.size() / 2;
                    if (*home >= maxEarn) {
                        token = "";
                        *home -= maxEarn;
                    } else {
                        token = token.substr(*home*2);
                        *home = 0;
                    }
                } else if (*away) {
                    int maxEarn = (token.size()-1) / 2;
                    if (*away >= maxEarn) {
                        token = "";
                        *away -= maxEarn;
                    } else {
                        token = token.substr(1+*away*2);
                        *away = 0;
                    }
                } else {
                    token = "";
                }
            }
        }

        io.writeYes(c == 0 && d == 0);
    });
    
    return 0;
}