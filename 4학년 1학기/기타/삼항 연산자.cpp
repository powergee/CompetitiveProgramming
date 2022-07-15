#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>

struct Relation {
    char lhs, rhs;
    bool equal;
};

class Node {
public:
    virtual bool isLeaf() = 0;
    virtual char getRepr() = 0;
};

class Boolean : public Node {
private:
    bool literal;
public:
    Boolean(const std::string& code, int& start) {
        literal = code[start++] == '1';
    }

    bool isLeaf() {
        return true;
    }

    char getRepr() {
        return literal ? '1' : '0';
    }
};

class Variable : public Node {
private:
    char id;
public:
    Variable(const std::string& code, int& start) {
        id = code[start++];
    }

    bool isLeaf() {
        return true;
    }

    char getRepr() {
        return id;
    }
};

// Boolean or Variable
class Value : public Node {
private:
    Node* inner;
public:
    Value(const std::string& code, int& start) {
        inner = (isalpha(code[start]) ? (Node*)(new Variable(code, start)) : (Node*)(new Boolean(code, start)));
    }

    bool isLeaf() {
        return true;
    }

    char getRepr() {
        return inner->getRepr();
    }
};

class Condition : public Node {
private:
    Value *left, *right;
public:
    Condition(Value* left, Value* right) : left(left), right(right) {}

    bool isLeaf() {
        return false;
    }

    char getRepr() {
        return 0;
    }

    char getLeftRepr() {
        return left->getRepr();
    }

    char getRightRepr() {
        return right->getRepr();
    }
};

class Expression : public Node {
private:
    Value* singleValue = nullptr;
    Condition* cond;
    Expression *exp1, *exp2;

    int countZeroCases(std::vector<Relation>& rels) {
        if (isLeaf()) {
            std::map<char, std::vector<std::pair<char, bool>>> graph;
            graph['0'].emplace_back('1', false);
            graph['1'].emplace_back('0', false);
            graph['0'].emplace_back(singleValue->getRepr(), true);
            graph[singleValue->getRepr()].emplace_back('0', true);
            std::vector<char> vertices { '0', '1' };
            for (char ch = 'a'; ch < 'a'+VAR_CNT; ++ch) {
                vertices.push_back(ch);
            }

            for (auto rel : rels) {
                graph[rel.lhs].emplace_back(rel.rhs, rel.equal);
                graph[rel.rhs].emplace_back(rel.lhs, rel.equal);
            }

            std::set<char> visited;
            std::map<char, bool> assigned;
            std::function<bool(char, bool)> assignValue = [&](char start, bool value) -> bool {
                visited.insert(start);
                assigned[start] = value;

                for (auto [next, equal] : graph[start]) {
                    if (visited.count(next) == 0) {
                        bool subResult = assignValue(next, equal ? value : !value);
                        if (!subResult) {
                            return false;
                        }
                    } else if ((equal ? value : !value) != assigned[next]) {
                        return false;
                    }
                }
                return true;
            };
            bool valid = assignValue('0', false);
            int compCnt = 1;

            for (char v : vertices) {
                if (visited.count(v) == 0) {
                    bool sub = assignValue(v, false);
                    compCnt++;
                    if (!sub) {
                        valid = false;
                    }
                }
            }
            return valid ? (1<<(compCnt-1)) : 0;
        } else {
            int result = 0;
            rels.push_back({cond->getLeftRepr(), cond->getRightRepr(), true});
            result += exp1->countZeroCases(rels);
            rels.back().equal = false;
            result += exp2->countZeroCases(rels);
            rels.pop_back();
            return result;
        }
    }

public:
    static int VAR_CNT;

    Expression(const std::string& code, int& start) {
        Value* val = new Value(code, start);
        if (code[start] == '=') { // Condition on the left
            start += 2; // ignore equals
            Value* right = new Value(code, start);
            cond = new Condition(val, right);
            ++start;
            exp1 = new Expression(code, start);
            ++start;
            exp2 = new Expression(code, start);
        } else { // Expression is single Value
            singleValue = val;
        }
    }

    bool isLeaf() {
        return (singleValue ? true : false);
    }

    char getRepr() {
        return (isLeaf() ? singleValue->getRepr() : 0);
    }

    int countZeroCases() {
        std::vector<Relation> rels;
        return countZeroCases(rels);
    }
};

int Expression::VAR_CNT = 0;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    Expression::VAR_CNT = n;

    std::string expr;
    std::cin >> expr;
    int start = 0;
    Expression program(expr, start);
    std::cout << program.countZeroCases();

    return 0;
}