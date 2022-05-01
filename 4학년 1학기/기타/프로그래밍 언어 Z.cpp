#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
#define MOD 10000LL

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

class Executable {
public:
    virtual Matrix execute(Matrix memory) = 0;
    virtual std::string name() const = 0;
};

class Arithmetic : public Executable {
private:
    Matrix coeff;
    Arithmetic() : coeff(27, 27) {}

public:
    Arithmetic(std::string line) : Arithmetic() {
        int start = line.find_first_not_of(' ');
        int eq = line.find_first_of('=', start);
        int lhs = line[start]-'a'+1;
        
        std::map<int, int> combs;
        int sign = 1;
        std::string constStr = "";
        for (int i = eq+1; i < line.size(); ++i) {
            if (line[i] == ' ') { continue; }
            if (isalpha(line[i])) {
                int var = line[i]-'a'+1;
                combs[var] += sign * std::stoi(constStr == "" ? "1" : constStr);
                sign = 1;
                constStr = "";
            } else if (isdigit(line[i])) {
                constStr += line[i];
            } else { // + or -
                if (constStr != "") {
                    combs[0] += sign * std::stoi(constStr);
                    sign = 1;
                    constStr = "";
                }
                sign = (line[i] == '+' ? 1 : -1);
            }
        }
        if (constStr != "") {
            combs[0] += sign * std::stoi(constStr);
        }

        for (int i = 0; i < 27; ++i) {
            if (i == lhs) {
                for (auto [var, con] : combs) {
                    coeff.at(i, var) += con;
                }
            } else {
                coeff.at(i, i) = 1;
            }
        }
    }

    Matrix execute(Matrix memory) {
        return coeff * memory;
    }

    void merge(const Arithmetic& after) {
        coeff = after.coeff * coeff;
    }

    void pow(int e) {
        coeff = coeff.getPow(e);
    }

    std::string name() const {
        return "Arithmetic";
    }
};

class Print : public Executable {
private:
    int var;

public:
    Print(std::string line) {
        var = line.back()-'a'+1;
    }

    Matrix execute(Matrix memory) {
        std::cout << char(var+'a'-1) << " = " << memory.at(var, 0) << "\n";
        return memory;
    }

    std::string name() const {
        return "Print";
    }
};

class ForLoop : public Executable {
private:
    int loopCount = 0;
    std::vector<Executable*> statements;
    Arithmetic* optimized = nullptr;

public:
    ForLoop(std::vector<std::string>& lines, int& start) {
        loopCount = std::stoi(lines[start].substr(lines[start].find_first_of('T')+2));
        ++start;

        Arithmetic* arithBuffer = nullptr;
        auto updateBuffer = [&](Arithmetic* mult) {
            if (arithBuffer) {
                arithBuffer->merge(*mult);
            } else {
                arithBuffer = new Arithmetic(*mult);
            }
        };
        auto flushBuffer = [&]() {
            if (arithBuffer) {
                statements.push_back(arithBuffer);
                arithBuffer = nullptr;
            }
        };

        while (start < lines.size()) {
            int firstIdx = lines[start].find_first_not_of(' ');
            char first = lines[start][firstIdx];
            if (first == 'S') {
                break;
            } else if (first == 'P') {
                flushBuffer();
                Print* p = new Print(lines[start]);
                statements.push_back(p);
            } else if (first == 'R') {
                ForLoop* f = new ForLoop(lines, start);
                if (f->optimized) {
                    updateBuffer(f->optimized);
                } else {
                    flushBuffer();
                    statements.push_back(f);
                }
            } else {
                Arithmetic* a = new Arithmetic(lines[start]);
                updateBuffer(a);
            }
            ++start;
        }
        flushBuffer();

        if (statements.size() == 1 && statements.back()->name() == "Arithmetic") {
            optimized = (Arithmetic*)statements.back();
            optimized->pow(loopCount);
        }
    }

    Matrix execute(Matrix memory) {
        if (optimized) {
            return optimized->execute(memory);
        }
        for (int i = 0; i < loopCount; ++i) {
            for (Executable* st : statements) {
                memory = st->execute(memory);
            }
        }
        return memory;
    }

    std::string name() const {
        return "ForLoop";
    }
};

class Program : public Executable {
private:
    std::vector<Executable*> statements;

public:
    Program(std::vector<std::string>& lines) {
        for (int i = 0; i < lines.size(); ++i) {
            int firstIdx = lines[i].find_first_not_of(' ');
            char first = lines[i][firstIdx];
            if (first == 'B') {
                continue;
            } else if (first == 'S') {
                break;
            } else if (first == 'P') {
                Print* p = new Print(lines[i]);
                statements.push_back(p);
            } else if (first == 'R') {
                ForLoop* f = new ForLoop(lines, i);
                statements.push_back(f);
            } else {
                Arithmetic* a = new Arithmetic(lines[i]);
                statements.push_back(a);
            }
        }
    }

    Matrix execute(Matrix memory) {
        for (Executable* st : statements) {
            memory = st->execute(memory);
        }
        return memory;
    }

    std::string name() const {
        return "Program";
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::vector<std::string> lines;
    do {
        std::string line;
        std::getline(std::cin, line);
        lines.push_back(line);
    } while (lines.back() != "STOP");

    Program p(lines);
    Matrix memory(27, 1);
    memory.at(0, 0) = 1;
    p.execute(memory);

    return 0;
}