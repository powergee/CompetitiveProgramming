#include <iostream>
#include <vector>
#include <cassert>
#define MOD 1000000007

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
    int n, m;
    scanf("%d %d", &n, &m);

    Matrix state(n, 1);
    state(0, 0) = 1;

    Matrix coeff(n, n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        coeff(a-1, b-1) += 1;
        coeff(b-1, a-1) += 1;
    }

    int d;
    scanf("%d", &d);

    printf("%lld", (coeff.getPow(d) * state).at(0, 0));

    return 0;
}