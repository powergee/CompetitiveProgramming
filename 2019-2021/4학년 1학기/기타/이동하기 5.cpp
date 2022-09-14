#include <iostream>
#include <algorithm>
#include <vector>

struct IO {
    IO() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
    }

    int readInt() {
        int v;
        std::cin >> v;
        return v;
    }

    double readDouble() {
        double v;
        std::cin >> v;
        return v;
    }

    std::string readToken() {
        std::string t;
        std::cin >> t;
        return t;
    }

    std::vector<int> readInts(int n) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        return arr;
    }

    std::vector<int> readInts() {
        int n = readInt();
        return readInts(n);
    }

    template<typename T>
    void write(T value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void write(T value, Args... args) {
        std::cout << value << " ";
        write(args...);
    }
};

int main() {
    IO io;
    int n = io.readInt(), m = io.readInt();
    auto row = io.readInts(n);
    auto col = io.readInts(m);

    int rowMax = *std::max_element(row.begin(), row.end());
    int colMax = *std::max_element(col.begin(), col.end());

    int rowLastMax = 0;
    for (int i = row.size()-1; i >= 0; --i) {
        if (row[i] == rowMax) {
            rowLastMax = i;
            break;
        }
    }
    
    int i = 0, j = 0;
    long long answer = 0;
    auto update = [&](int r, int c) {
        answer += row[r]*1000000000LL + col[c];
    };
    update(0, 0);

    while (row[i] < rowMax) {
        update(++i, j);
    }
    while (col[j] < colMax) {
        update(i, ++j);
    }
    while (i < rowLastMax) {
        update(++i, j);
    }
    while (j+1 < m) {
        update(i, ++j);
    }
    while (i+1 < n) {
        update(++i, j);
    }

    io.write(answer);

    return 0;
}