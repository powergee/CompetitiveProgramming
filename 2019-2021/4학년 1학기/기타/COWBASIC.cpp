#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#define MOD 1000000007LL

using Long = long long;

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
            data[i] = std::vector<Long>(c, 0);
        }
    }

    int getRows() { return rows; }
    int getCols() { return cols; }
    Long at(int r, int c) const { return data[r][c]; }
    Long& at(int r, int c) { return data[r][c]; }
    Long operator()(int r, int c) const { return data[r][c]; }
    Long& operator()(int r, int c) { return data[r][c]; }

    Matrix operator*(const Matrix& m) const {
        assert(cols == m.rows);
        Matrix result(rows, m.cols);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < m.cols; ++c) {
                result(r, c) = 0;
                for (int i = 0; i < cols; ++i) {
                    result(r, c) += (((at(r, i)+MOD)%MOD) * ((m(i, c)+MOD)%MOD)) % MOD;
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
};

std::string getToken(const std::string& line, int& start) {
    int tokenStart = line.find_first_not_of(' ', start);
    int tokenEnd = line.find_first_of(' ', tokenStart);
    if (tokenEnd == line.npos) {
        tokenEnd = line.size();
    }
    start = tokenEnd;
    return line.substr(tokenStart, tokenEnd-tokenStart);
}

class BasicBlock {
private:
    Matrix compressed;

public:
    BasicBlock(
        const std::map<std::string, int>& varTable,
        const std::vector<std::string> codes,
        int& cIdx)
     : compressed(varTable.size(), varTable.size()) {
        for (int i = 0; i < varTable.size(); ++i) {
            compressed(i, i) = 1;
        }
        
        for (; cIdx < codes.size(); ++cIdx) {
            int index = 0;
            std::string first = getToken(codes[cIdx], index);
            
            if (first[0] == '}' || first[0] == 'R') { // end of block
                break;
            } else if (isdigit(first[0])) { // loop
                Long loopCount = std::stoll(first);
                BasicBlock loopBlock(varTable, codes, ++cIdx);
                compressed = loopBlock.compressed.getPow(loopCount) * compressed;
            } else { // assignment
                int lhs = varTable.at(first);
                getToken(codes[cIdx], index); // ignore equal

                std::map<int, Long> coeff;
                while (index < codes[cIdx].size()) {
                    std::string rhs = getToken(codes[cIdx], index);

                    if (rhs == "(" || rhs == ")" || rhs == "+") {
                        continue;
                    } else if (isdigit(rhs[0])) {
                        coeff[0] += std::stoll(rhs);
                    } else {
                        coeff[varTable.at(rhs)]++;
                    }
                }

                Matrix curr(varTable.size(), varTable.size());
                for (int i = 0; i < varTable.size(); ++i) {
                    if (i == lhs) {
                        for (auto [var, con] : coeff) {
                            curr(i, var) += con;
                        }
                    } else {
                        curr(i, i) = 1;
                    }
                }

                compressed = curr * compressed;
            }
        }
    }

    Matrix execute(Matrix memory) {
        return compressed * memory;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::map<std::string, int> varTable;
    varTable["1"] = 0;
    int target;
    std::vector<std::string> codes;
    do {
        std::string line;
        std::getline(std::cin, line);
        int start = 0;
        std::string first = getToken(line, start);
        if ('a' <= first[0] && first[0] <= 'z' && varTable.count(first) == 0) {
            varTable[first] = varTable.size();
        } else if  (first[0] == 'R') {
            std::string var = getToken(line, start);
            target = varTable[var];
        }
        codes.push_back(line);
    } while (codes.back().front() != 'R');

    Matrix memory(varTable.size(), 1);
    memory(0, 0) = 1;

    int start = 0;
    BasicBlock program(varTable, codes, start);
    memory = program.execute(memory);
    std::cout << memory(target, 0);

    return 0;
}