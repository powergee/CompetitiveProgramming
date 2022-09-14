#include <iostream>
#include <vector>
#include <cassert>
#define MOD 1000003

typedef long long Long;

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<Long>> data;
    
public:
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data.resize(r);
        for (int i = 0; i < r; ++i) {
            data[i] = std::vector<Long>(c);
        }
    }

    int getRows() { return rows; }
    int getCols() { return cols; }
    Long at(int r, int c) const { return data[r][c]; }
    Long& at(int r, int c) { return data[r][c]; }
    Long operator()(int r, int c) const { return data[r][c]; }
    Long& operator()(int r, int c) { return data[r][c]; }

    Matrix& operator+=(const Matrix& m) {
        assert(rows == m.rows && cols == m.cols);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                at(r, c) = (at(r, c) + m(r, c)) % MOD;
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& m) const {
        Matrix result = *this;
        result += m;
        return result;
    };

    Matrix& operator-=(const Matrix& m) {
        assert(rows == m.rows && cols == m.cols);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                at(r, c) = (at(r, c) - m(r, c) + MOD) % MOD;
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix& m) const {
        Matrix result = *this;
        result -= m;
        return result;
    };

    Matrix operator*(const Matrix& m) const {
        assert(cols == m.rows);
        Matrix result(rows, m.cols);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < m.cols; ++c) {
                result(r, c) = 0;
                for (int i = 0; i < cols; ++i) {
                    result(r, c) += (at(r, i) * m(i, c)) % MOD;
                    result(r, c) %= MOD;
                }
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix& m) {
        Matrix result = *this * m;
        *this = result;
        return *this;
    }

    Matrix getPow(Long exp) const {
        assert(exp >= 0 && rows == cols);
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            result.at(i, i) = 1;
        }
        Matrix sub = *this;

        while (exp > 0) {
            if (exp & 1) {
                result *= sub;
            }
            sub *= sub;
            exp /= 2;
        }
        return result;
    }

    void print() const {
        for (int r = 0; r < rows; ++r) {
            std::cout << "[ " << data[r][0];
            for (int c = 1; c < cols; ++c) {
                std::cout << ", " << data[r][c];
            }
            std::cout << " ]\n";
        }
    }
};

int main() {
    int n, s, e, t;
    scanf("%d %d %d %d", &n, &s, &e, &t);

    Matrix state(5*n, 1);
    state(s-1, 0) = 1;
    Matrix coeff(5*n, 5*n);

    for (int i = 0; i < n; ++i) {
        char line[n+1];
        scanf("%s", line);
        for (int j = 0; j < n; ++j) {
            int cost = line[j]-'0';
            if (cost) {
                coeff(j, i+n*(cost-1)) += 1;
            }
        }
    }
    for (int t = 1; t < 5; ++t) {
        for (int v = 0; v < n; ++v) {
            coeff(n*t+v, n*(t-1)+v) += 1;
        }
    }

    state = coeff.getPow(t) * state;
    std::cout << state(e-1, 0);

    return 0;
}